/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_chase_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 07:12:46 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/05 19:45:15 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D_bonus.h"

void	set_player_look_at(t_player *player, t_fvec enemy_pos)
{
	t_fvec		new_dir;
	float		magnitude;
	const float	smoothness = 0.5;

	new_dir.x = enemy_pos.x - player->pos.x;
	new_dir.y = enemy_pos.y - player->pos.y;
	magnitude = sqrtf(new_dir.x * new_dir.x + new_dir.y * new_dir.y);
	if (magnitude != 0)
	{
		new_dir.x /= magnitude;
		new_dir.y /= magnitude;
	}
	player->dir.x += (new_dir.x - player->dir.x) * smoothness;
	player->dir.y += (new_dir.y - player->dir.y) * smoothness;
	player->plane.x = -player->dir.y * 0.66;
	player->plane.y = player->dir.x * 0.66;
}

void	enemy_game_over(t_game *game)
{
	if (game->pwl.item.collected)
		return ;
	if (!game->state[S_CAUGHT])
		write(1, "\a", 1);
	game->state[S_MAP_DISABLE] = 1;
	set_player_look_at(&game->player, game->enemy.pos);
	if (game->player.zoom < 1.8)
		game->player.zoom += 0.1;
	game->player.pitch = -300;
	game->state[S_CAUGHT] = 1;
}

void	enemy_open_door(t_game *game)
{
	if (game->map.arr[(int)game->enemy.pos.y][(int)game->enemy.pos.x] == 2)
		game->map.arr[(int)game->enemy.pos.y][(int)game->enemy.pos.x] = -2;
	if (game->map.arr[(int)game->enemy.pos.y - 1][(int)game->enemy.pos.x] == 2)
		game->map.arr[(int)game->enemy.pos.y - 1][(int)game->enemy.pos.x] = -2;
	if (game->map.arr[(int)game->enemy.pos.y + 1][(int)game->enemy.pos.x] == 2)
		game->map.arr[(int)game->enemy.pos.y + 1][(int)game->enemy.pos.x] = -2;
	if (game->map.arr[(int)game->enemy.pos.y][(int)game->enemy.pos.x - 1] == 2)
		game->map.arr[(int)game->enemy.pos.y][(int)game->enemy.pos.x - 1] = -2;
	if (game->map.arr[(int)game->enemy.pos.y][(int)game->enemy.pos.x + 1] == 2)
		game->map.arr[(int)game->enemy.pos.y][(int)game->enemy.pos.x + 1] = -2;
	game->map.update = 1;
}

void	enemy_chase(t_game *game, float dist_sq, float speed)
{
	if (game->state[S_ENEMY_VISION] == 1)
	{
		game->enemy.last_seen.x = game->player.pos.x;
		game->enemy.last_seen.y = game->player.pos.y;
		game->enemy.last_dist.x = game->enemy.dist.x;
		game->enemy.last_dist.y = game->enemy.dist.y;
	}
	game->enemy.memory.x = game->enemy.pos.x + game->enemy.last_dist.x * speed;
	game->enemy.memory.y = game->enemy.pos.y + game->enemy.last_dist.y * speed;
	if (dist_sq < 1.415)
		return (enemy_game_over(game));
	enemy_open_door(game);
	if (((int)game->enemy.pos.x == (int)game->enemy.last_seen.x
			&& (int)game->enemy.pos.y == (int)game->enemy.last_seen.y)
		|| check_collision(&game->enemy.pos,
			game->enemy.memory, ENEMY_RADIUS, game))
	{
		game->enemy.last_seen.x = 0;
		game->enemy.last_seen.y = 0;
		game->enemy.memory.x = 0;
		game->enemy.memory.y = 0;
	}
}

void	update_enemy_pos(t_game *game)
{
	float	dist_sq;
	float	normalized_speed;

	if (game->state[S_ENEMY_DEAD])
		return ;
	if (game->state[S_ENEMY_VISION] == 0 && (game->enemy.memory.x == 0
			&& game->enemy.memory.y == 0))
		return (enemy_hunt(game));
	game->enemy.dist.x = game->player.pos.x - game->enemy.pos.x;
	game->enemy.dist.y = game->player.pos.y - game->enemy.pos.y;
	dist_sq = game->enemy.dist.x * game->enemy.dist.x + game->enemy.dist.y
		* game->enemy.dist.y;
	normalized_speed = (ENEMY_SPD * game->frame.time) / sqrtf(dist_sq);
	if (game->pwl.item.collected)
		normalized_speed = -normalized_speed;
	enemy_chase(game, dist_sq, normalized_speed);
}
