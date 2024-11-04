/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 07:28:06 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/04 08:19:08 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	render_item_sprite(t_game *game, t_coin item)
{
	t_fvec	view;
	t_fvec	screen;
	t_fvec	scale;
	float	dist_sqrt;
	float	scaling;

	dist_sqrt = sqrtf(item.dist.x * item.dist.x + item.dist.y * item.dist.y);
	if (dist_sqrt > 3)
		return ;
	view.x = dot_product(game->player.dir, item.dist) * 0.88;
	if (view.x >= 0)
		return ;
	view.y = dot_product(game->player.plane, item.dist);
	screen.x = (RES_X * (view.y * 2.0) / (2 * view.x)) * game->player.zoom;
	screen.y = (float)-game->player.pitch;
	scaling = fmaxf((game->img[T_ITEM].size.x / dist_sqrt) * game->player.zoom
			* 0.04, 0.04);
	scale.x = scaling;
	scale.y = scaling;
	if (screen.x < -RES_X2 - 32 * scaling || screen.x > RES_X2 + 32 * scaling
		|| (screen.y + game->img[T_ITEM].size.y * scaling) > 382)
		return ;
	put_img_scale_mid_bot((t_vec){screen.x, screen.y}, &game->img[T_ITEM],
		&game->img[T_WIN], scale);
}

void	render_item(t_game *game)
{
	t_ray	r;
	int		i;

	i = 0;
	while (i < game->item.count)
	{
		if (game->item.arr[i].collected == 1)
		{
			i++;
			continue ;
		}
		init_ray_to_target(game, &r, game->item.arr[i].pos);
		if (dda_to_target(game, &r, game->item.arr[i].pos) != 1)
		{
			i++;
			continue ;
		}
		game->item.arr[i].dist.x = game->player.pos.x - game->item.arr[i].pos.x;
		game->item.arr[i].dist.y = game->player.pos.y - game->item.arr[i].pos.y;
		render_item_sprite(game, game->item.arr[i]);
		i++;
	}
}

int	same_position(t_fvec p1, t_fvec p2)
{
	if ((int)p1.x == (int)p2.x && (int)p1.y == (int)p2.y)
		return (1);
	return (0);
}

void	pickup_item(t_game *game)
{
	int	i;

	if (game->map.arr[(int)game->player.pos.y][(int)game->player.pos.x]
		== TILE_ITEM)
	{
		i = 0;
		while (i < game->item.count)
		{
			if (same_position(game->player.pos, game->item.arr[i].pos))
			{
				game->item.collected++;
				game->item.arr[i].collected = 1;
				game->map.arr[(int)game->player.pos.y][(int)game->player.pos.x]
					= 0;
				game->map.update = 1;
				return ;
			}
			i++;
		}
	}
}
