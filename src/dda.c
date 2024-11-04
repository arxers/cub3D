/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 07:00:31 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/04 08:00:58 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

// Sets a rays direction, based on the player direction vector.
// camera_x determines the angle in which ray originates from.
// < 0: left of center, 0: center, > 0: right of center
// flag for zoom can be enabled to include the players zoom in the calculation.
void	set_ray_direction(t_game *game, t_ray *r, float camera_x, int incl_zoom)
{
	float	zoom;

	r->map.x = (int)game->player.pos.x;
	r->map.y = (int)game->player.pos.y;
	zoom = game->player.zoom;
	if (!incl_zoom)
		zoom = 1;
	r->dir.x = game->player.dir.x * zoom + game->player.plane.x * camera_x;
	r->dir.y = game->player.dir.y * zoom + game->player.plane.y * camera_x;
	if (r->dir.x == 0)
		r->delta_dist.x = 1E+37;
	else
		r->delta_dist.x = fabsf(1 / r->dir.x);
	if (r->dir.y == 0)
		r->delta_dist.y = 1E+37;
	else
		r->delta_dist.y = fabsf(1 / r->dir.y);
}

// Determine the ray's array traversal direction (up, down, left, or right),
// and how far it should increment itself in the array.
void	set_ray_step_direction(t_game *game, t_ray *r)
{
	if (r->dir.x < 0)
	{
		r->step.x = -1;
		r->side_dist.x = (game->player.pos.x - r->map.x) * r->delta_dist.x;
	}
	else
	{
		r->step.x = 1;
		r->side_dist.x = (r->map.x + 1.0 - game->player.pos.x)
			* r->delta_dist.x;
	}
	if (r->dir.y < 0)
	{
		r->step.y = -1;
		r->side_dist.y = (game->player.pos.y - r->map.y) * r->delta_dist.y;
	}
	else
	{
		r->step.y = 1;
		r->side_dist.y = (r->map.y + 1.0 - game->player.pos.y)
			* r->delta_dist.y;
	}
}

// Determines the traversal direction,
// by comparing the distance a ray has to traverse, during a dda cycle.
void	set_dda_step_side(t_ray *r)
{
	if (r->side_dist.x < r->side_dist.y)
	{
		r->side_dist.x += r->delta_dist.x;
		r->map.x += r->step.x;
		r->side = VERTICAL;
	}
	else
	{
		r->side_dist.y += r->delta_dist.y;
		r->map.y += r->step.y;
		r->side = HORIZONTAL;
	}
}

// Shoots a ray until it has hit a value in the array larger than 0.
int	dda(t_ray *r, t_game *game)
{
	while (1)
	{
		set_dda_step_side(r);
		if (out_of_bounds(r->map, game))
			return (-1);
		if (game->map.arr[(int)r->map.y][(int)r->map.x] > 0
			&& game->map.arr[(int)r->map.y][(int)r->map.x] != TILE_PWL)
			return (0);
	}
}
