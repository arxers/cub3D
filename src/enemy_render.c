/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 07:34:20 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/04 08:01:21 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	update_enemy_sprite(t_game *game)
{
	game->enemy.img = game->img[game->enemy.frame];
	if (!game->pwl.item.collected)
	{
		game->enemy.frame++;
		if (game->enemy.frame == T_XENO7 + 1)
			game->enemy.frame = T_XENO0;
		return ;
	}
	game->enemy.frame--;
	if (game->enemy.frame == T_XENO0 -1)
		game->enemy.frame = T_XENO7;
}

void	render_enemy(t_game *game)
{
	t_fvec	view;
	t_fvec	screen;
	t_fvec	scale;
	float	dist_sqrt;
	float	scaling;

	game->state[S_ENEMY_VISION] = 1;
	view.x = dot_product(game->player.dir, game->enemy.dist) * 0.9;
	if (view.x >= 0)
		return ;
	dist_sqrt = sqrtf(game->enemy.dist.x * game->enemy.dist.x
			+ game->enemy.dist.y * game->enemy.dist.y);
	view.y = dot_product(game->player.plane, game->enemy.dist);
	screen.x = (RES_X * (view.y * 2.0) / (2 * view.x)) * game->player.zoom;
	screen.y = ((RES_Y * game->player.z) / dist_sqrt - game->player.pitch);
	scaling = fmaxf((game->img[T_XENO0].size.x / dist_sqrt)
			* game->player.zoom * 0.1, 0.1);
	scale.x = scaling;
	scale.y = scaling;
	if (view.x < 0)
		put_img_scale_mid((t_vec){screen.x, screen.y},
			&game->enemy.img, &game->img[T_WIN], scale);
}

void	render_enemy_sprite(t_game *game)
{
	t_ray	r;

	if (game->state[S_ENEMY_DEAD])
		return ;
	if (delay_ms(75, &game->timer[MS100]))
	{
		game->state[S_ENEMY_ICON] = !game->state[S_ENEMY_ICON];
		update_enemy_sprite(game);
	}
	init_ray_to_target(game, &r, game->enemy.pos);
	if (dda_to_target(game, &r, game->enemy.pos) != 1)
	{
		game->state[S_ENEMY_VISION] = 0;
		return ;
	}
	render_enemy(game);
}
