/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwl_render_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 07:24:48 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/05 19:42:57 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D_bonus.h"

void	set_pwl_view(t_game *game, t_ray r)
{
	if (r.dir.x > 0.5 && r.dir.y < -0.5)
		game->pwl.item_img = game->img[T_PWL0];
	else if (r.dir.x > 0.5 && r.dir.y > 0.5)
		game->pwl.item_img = game->img[T_PWL2];
	else if (r.dir.x < -0.5 && r.dir.y > 0.5)
		game->pwl.item_img = game->img[T_PWL4];
	else if (r.dir.x < -0.5 && r.dir.y < -0.5)
		game->pwl.item_img = game->img[T_PWL6];
	else if (r.dir.x > 0.5)
		game->pwl.item_img = game->img[T_PWL1];
	else if (r.dir.y > 0.5)
		game->pwl.item_img = game->img[T_PWL3];
	else if (r.dir.x < -0.5)
		game->pwl.item_img = game->img[T_PWL5];
	else if (r.dir.y < -0.5)
		game->pwl.item_img = game->img[T_PWL7];
}

void	render_pwl_sprite(t_game *game, t_ray r)
{
	t_fvec	view;
	t_fvec	screen;
	t_fvec	scale;
	float	dist_sq;
	float	scaling;

	game->pwl.item.dist.x = game->player.pos.x - game->pwl.item.pos.x;
	game->pwl.item.dist.y = game->player.pos.y - game->pwl.item.pos.y;
	view.x = dot_product(game->player.dir, game->pwl.item.dist) * 0.88;
	if (view.x >= 0)
		return ;
	dist_sq = sqrtf(game->pwl.item.dist.x * game->pwl.item.dist.x
			+ game->pwl.item.dist.y * game->pwl.item.dist.y);
	view.y = dot_product(game->player.plane, game->pwl.item.dist);
	screen.x = (RES_X * (view.y * 2.0) / (2 * view.x)) * game->player.zoom;
	screen.y = ((RES_Y * game->player.z) / dist_sq - game->player.pitch);
	scaling = fmaxf((game->img[T_ITEM].size.x / dist_sq)
			* game->player.zoom * 0.1, 0.1);
	scale.x = scaling;
	scale.y = scaling;
	set_pwl_view(game, r);
	game->pwl.item_img.intensity = set_intensity(game->light, dist_sq);
	put_img_scale_darken((t_vec){screen.x, screen.y},
		&game->pwl.item_img, &game->img[T_WIN], scale);
}

void	pwl_hit_check(t_game *game)
{
	t_ray	r;
	float	dist_sq;

	dist_sq = game->enemy.dist.x * game->enemy.dist.x
		+ game->enemy.dist.y * game->enemy.dist.y;
	set_ray_direction(game, &r, 0, 0);
	set_ray_step_direction(game, &r);
	if (dda_to_target(game, &r, game->enemy.pos) && dist_sq < 4)
		game->state[S_ENEMY_DEAD] = 1;
}

void	render_pwl_overlay(t_game *game)
{
	if (game->state[S_PUNCHING] == 1)
	{
		if (delay_ms(100, &game->timer[TIMER_PWL]))
		{
			game->pwl.frame++;
			game->pwl.overlay_img = game->img[game->pwl.frame];
			if (game->pwl.frame == T_PWL_ARM6 + 1)
			{
				game->pwl.frame = T_PWL_ARM0;
				game->pwl.overlay_img = game->img[T_PWL_ARM0];
				game->state[S_PUNCHING] = 0;
			}
		}
		if (game->pwl.frame == T_PWL_ARM4)
			pwl_hit_check(game);
	}
	if (game->player.zoom == 1)
		return (put_img((t_vec){0, 136},
			&game->pwl.overlay_img, &game->img[T_WIN]));
	put_img_scale_mid((t_vec){0, 68}, &game->pwl.overlay_img,
		&game->img[T_WIN], (t_fvec){game->player.zoom, game->player.zoom});
}

void	render_pwl(t_game *game)
{
	t_ray	r;

	if (game->pwl.item.collected == 1)
		return (render_pwl_overlay(game));
	init_ray_to_target(game, &r, game->pwl.item.pos);
	if (dda_to_target(game, &r, game->pwl.item.pos) != 1)
		return ;
	render_pwl_sprite(game, r);
}
