/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_special_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:00:38 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/05 19:45:21 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D_bonus.h"

void	init_ray_to_target(t_game *game, t_ray *r, t_fvec target_pos)
{
	float	magnitude;

	r->dir.x = target_pos.x - game->player.pos.x;
	r->dir.y = target_pos.y - game->player.pos.y;
	magnitude = sqrtf(r->dir.x * r->dir.x + r->dir.y * r->dir.y);
	r->dir.x /= magnitude;
	r->dir.y /= magnitude;
	r->map.x = (int)game->player.pos.x;
	r->map.y = (int)game->player.pos.y;
	r->delta_dist.x = fabsf(1 / r->dir.x);
	r->delta_dist.y = fabsf(1 / r->dir.y);
	set_ray_step_direction(game, r);
}

int	dda_to_target(t_game *game, t_ray *r, t_fvec target_pos)
{
	if ((int)target_pos.x == (int)game->player.pos.x
		&& (int)target_pos.y == (int)game->player.pos.y)
		return (1);
	while (1)
	{
		set_dda_step_side(r);
		if (out_of_bounds(r->map, game)
			|| (game->map.arr[(int)r->map.y][(int)r->map.x] > 0
			&& game->map.arr[(int)r->map.y][(int)r->map.x] != TILE_PWL))
			return (0);
		if ((int)r->map.x == (int)target_pos.x
			&& (int)r->map.y == (int)target_pos.y)
			return (1);
	}
}

int	dda_interact(t_ray *r, t_game *game)
{
	int	i;
	int	tile_hit;

	i = 0;
	while (i < 3)
	{
		set_dda_step_side(r);
		if (out_of_bounds(r->map, game))
			return (0);
		tile_hit = game->map.arr[(int)r->map.y][(int)r->map.x];
		if (tile_hit == TILE_WALL)
			return (0);
		if (!out_of_bounds(r->map, game) && (tile_hit == TILE_PWL
				|| tile_hit == TILE_DOOR || tile_hit == TILE_DOOR_OPEN))
			return (game->map.arr[(int)r->map.y][(int)r->map.x]);
		i++;
	}
	return (0);
}
