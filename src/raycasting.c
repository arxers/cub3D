/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 07:52:38 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/04 23:23:37 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

// Draws vertical slices of the wall projections, from left to right.
void	draw_wall_slices(t_game *game, t_ray *r, t_tex *tex)
{
	tex->tex_step = 1.0 * WALL / r->line_height;
	r->pix.y = r->draw_start;
	tex->hit.y = (r->draw_start + game->player.pitch - (r->line_height
				* game->player.z) - (RES_Y - r->line_height) * 0.5)
		* tex->tex_step;
	while (r->pix.y < r->draw_end)
	{
		tex->coords.y = (int)tex->hit.y & (WALL - 1);
		tex->hit.y += tex->tex_step;
		set_pixel_alpha(&game->img[T_WIN], r->pix.x, r->pix.y,
			get_pixel(tex->wall_tex, tex->coords.x, tex->coords.y));
		r->pix.y++;
	}
}

// Determine the height of a vertical slice, based on how far a ray traversed.
void	calculate_wall_projection(t_game *game, t_ray *r, t_tex *tex)
{
	if (r->side == VERTICAL)
		r->wall_dist = r->side_dist.x - r->delta_dist.x;
	else
		r->wall_dist = r->side_dist.y - r->delta_dist.y;
	r->line_height = (int)(RES_Y / r->wall_dist);
	r->draw_start = (RES_Y - r->line_height) * 0.5 - game->player.pitch
		+ (r->line_height * game->player.z);
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = (r->line_height + RES_Y) * 0.5 - game->player.pitch
		+ (r->line_height * game->player.z);
	if (r->draw_end >= RES_Y)
		r->draw_end = RES_Y;
	if (r->side == VERTICAL)
		tex->hit.x = game->player.pos.y + r->wall_dist * r->dir.y;
	else
		tex->hit.x = game->player.pos.x + r->wall_dist * r->dir.x;
	tex->hit.x -= floorf(tex->hit.x);
	tex->coords.x = (int)(tex->hit.x * WALL);
}

void	assign_wall_textures(t_game *game, t_ray *r, t_tex *tex)
{
	if (r->side == VERTICAL)
	{
		tex->wall_tex = &game->img[T_WEST];
		if (r->dir.x <= 0)
		{
			tex->wall_tex = &game->img[T_EAST];
			tex->coords.x = WALL - tex->coords.x - 1;
		}
	}
	else if (r->side == HORIZONTAL)
	{
		tex->wall_tex = &game->img[T_NORTH];
		if (r->dir.y >= 0)
		{
			tex->wall_tex = &game->img[T_SOUTH];
			tex->coords.x = WALL - tex->coords.x - 1;
		}
	}
}

// Sets the img pointer in texture struct,
// based on the value in the array that the ray has hit.
void	assign_tile_textures(t_game *game, t_ray *r, t_tex *tex)
{
	tex->wall_tex = NULL;
	if (game->map.arr[(int)r->map.y][(int)r->map.x] < 1
		|| game->map.arr[(int)r->map.y][(int)r->map.x] == TILE_PWL)
		return ;
	if (game->map.arr[(int)r->map.y][(int)r->map.x] == 2)
	{
		if ((r->side == VERTICAL && r->dir.x <= 0) || (r->side == HORIZONTAL
				&& r->dir.y >= 0))
			tex->coords.x = WALL - tex->coords.x - 1;
		tex->wall_tex = &game->img[T_DOOR_CLOSE];
		return ;
	}
	assign_wall_textures(game, r, tex);
}

void	render_walls(t_game *game)
{
	t_tex			tex;
	t_ray			r;
	const float		camera_x_factor = 2.0 / RES_X;

	draw_bg(game);
	if (out_of_bounds(game->player.pos, game))
		return ;
	r.pix.x = 0;
	while (r.pix.x < RES_X)
	{
		set_ray_direction(game, &r, r.pix.x * camera_x_factor - 1, 1);
		set_ray_step_direction(game, &r);
		if (dda(&r, game) == -1)
			return ;
		calculate_wall_projection(game, &r, &tex);
		assign_tile_textures(game, &r, &tex);
		draw_wall_slices(game, &r, &tex);
		r.pix.x++;
	}
}
