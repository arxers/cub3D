/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 06:47:38 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/05 19:43:15 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D_bonus.h"

void	draw_tile(t_img *map, t_vec origin, int tile)
{
	const t_vec	size = (t_vec){MAP_CELL_SIZE - 1, MAP_CELL_SIZE - 1};

	if (tile == 2)
		draw_rectangle(map, (t_vec){origin.x + MAP_CELL_SIZE * 0.3,
			origin.y + MAP_CELL_SIZE * 0.3},
			(t_vec){MAP_CELL_SIZE * 0.3, MAP_CELL_SIZE * 0.3}, BLACK);
	else if (tile == -2)
		draw_rectangle(map, (t_vec){origin.x + MAP_CELL_SIZE * 0.1,
			origin.y + MAP_CELL_SIZE * 0.1},
			(t_vec){MAP_CELL_SIZE * 0.8, MAP_CELL_SIZE * 0.8}, BLACK);
	else if (tile == 3)
		draw_rectangle(map, origin, size, 0xFFAD1A);
	else if (tile <= 0)
		draw_rectangle(map, origin, size, BLACK);
	if (tile == -3)
		draw_circle(map, (t_vec){origin.x + MAP_CELL_SIZE * 0.5 - 1,
			origin.y + MAP_CELL_SIZE * 0.5 - 1},
			MAP_CELL_SIZE * 0.25, 0xFFAD1A);
}

void	update_map_tiles(t_game *game)
{
	t_vec	count;
	t_vec	origin;

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
			draw_tile(&game->img[T_MAP_TILES], origin,
				game->map.arr[count.y][count.x]);
			count.x++;
			origin.x += MAP_CELL_SIZE;
		}
		count.y++;
		origin.y += MAP_CELL_SIZE;
	}
	game->map.update = 0;
}

void	draw_map_enemy(t_game *game)
{
	t_vec		start;
	t_vec		end;

	start.x = (int)(game->enemy.pos.x * MAP_CELL_SIZE);
	start.y = (int)(game->enemy.pos.y * MAP_CELL_SIZE);
	end.x = (int)(game->enemy.last_seen.x * MAP_CELL_SIZE);
	end.y = (int)(game->enemy.last_seen.y * MAP_CELL_SIZE);
	if (delay_ms(200, &game->timer[TIMER_ENEMY_PATH]))
		draw_circle(&game->img[T_MAP_ENEMY_PATH], start, 1, WHITE);
	if (game->state[S_ENEMY_PATH])
		put_img((t_vec){0, 0},
			&game->img[T_MAP_ENEMY_PATH], &game->img[T_MAP]);
	if (game->enemy.last_seen.x && game->enemy.last_seen.y)
	{
		draw_line(&game->img[T_MAP], start, end, RED);
		draw_circle(&game->img[T_MAP], end, MAP_CELL_SIZE * 0.15, RED);
		draw_circle_outline(&game->img[T_MAP], end, MAP_CELL_SIZE * 0.25, RED);
	}
	if (game->state[S_ENEMY_ICON])
	{
		draw_circle(&game->img[T_MAP], start,
			MAP_CELL_SIZE * 0.5, MAP_COLOR);
		draw_circle_outline(&game->img[T_MAP], start,
			MAP_CELL_SIZE * 0.5, BLACK);
	}
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
	if (!game->state[S_ENEMY_DEAD])
		draw_map_enemy(game);
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
