/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 06:47:38 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/04 23:22:57 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	update_map_tiles(t_game *game)
{
	const t_vec	size = (t_vec){MAP_CELL_SIZE - 1, MAP_CELL_SIZE - 1};
	t_vec		count;
	t_vec		origin;

	draw_rectangle(&game->img[T_MAP_TILES], (t_vec){0, 0},
		game->img[T_MAP_TILES].size, MAP_COLOR);
	count.y = 0;
	origin.y = 0;
	while (count.y < game->map.size.y)
	{
		origin.x = 0;
		count.x = 0;
		while (count.x < game->map.size.x)
		{
			if (game->map.arr[count.y][count.x] == 0)
				draw_rectangle(&game->img[T_MAP_TILES], origin, size, BLACK);
			count.x++;
			origin.x += MAP_CELL_SIZE;
		}
		count.y++;
		origin.y += MAP_CELL_SIZE;
	}
	game->map.update = 0;
}

void	draw_map_player(t_img *img, t_player p)
{
	t_vec			player_pos;
	t_vec			pointer_pos;
	float			dir_radius;
	float			dir_dist;

	player_pos.x = (int)((p.pos.x * (float)MAP_CELL_SIZE));
	player_pos.y = (int)((p.pos.y * (float)MAP_CELL_SIZE));
	draw_circle(img, player_pos, MAP_CELL_SIZE * 0.15, WHITE);
	draw_circle_outline(img, player_pos, MAP_CELL_SIZE * 0.25, WHITE);
	dir_radius = MAP_CELL_SIZE * 0.15;
	dir_dist = 0.25;
	pointer_pos.x = (int)((p.pos.x + (p.dir.x * dir_dist * p.zoom))
			* (float)MAP_CELL_SIZE);
	pointer_pos.y = (int)((p.pos.y + (p.dir.y * dir_dist * p.zoom))
			* (float)MAP_CELL_SIZE);
	draw_circle(img, pointer_pos, dir_radius, WHITE);
}

void	draw_minimap(t_game *game)
{
	t_fvec		player_pos;
	const int	center = game->img[T_MAP_MASK].size.x * 0.5;

	if (game->state[S_MAP_DISABLE])
		return ;
	player_pos.x = (int)((game->player.pos.x * MAP_CELL_SIZE));
	player_pos.y = (int)((game->player.pos.y * MAP_CELL_SIZE));
	if (game->map.update)
		update_map_tiles(game);
	put_img((t_vec){0, 0}, &game->img[T_MAP_TILES], &game->img[T_MAP]);
	draw_map_player(&game->img[T_MAP], game->player);
	put_img((t_vec){0, 0,}, &game->img[T_MAP_BG], &game->img[T_MAP_MASK]);
	put_img((t_vec){-player_pos.x + center, -player_pos.y + center},
		&game->img[T_MAP], &game->img[T_MAP_MASK]);
	if (!game->state[S_MAP_BIG])
		put_img(game->map.offset, &game->img[T_MAP_MASK], &game->img[T_WIN]);
	else
		put_img((t_vec){RES_X2 - game->img[T_MAP].size.x * 0.5,
			RES_Y * 0.5 - game->img[T_MAP].size.y * 0.5},
			&game->img[T_MAP], &game->img[T_WIN]);
}
