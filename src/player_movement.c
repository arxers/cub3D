/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 07:40:32 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/04 23:30:35 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	calculate_movement(t_game *game, float *move_x, float *move_y)
{
	if (game->state[S_UP])
	{
		*move_x += game->player.dir.x;
		*move_y += game->player.dir.y;
	}
	if (game->state[S_DOWN])
	{
		*move_x -= game->player.dir.x;
		*move_y -= game->player.dir.y;
	}
	if (game->state[S_LEFT])
	{
		*move_x += game->player.dir.y;
		*move_y -= game->player.dir.x;
	}
	if (game->state[S_RIGHT])
	{
		*move_x -= game->player.dir.y;
		*move_y += game->player.dir.x;
	}
}

void	normalize_movement(float *move_x, float *move_y)
{
	float	len_sq;
	float	normalized_speed;

	len_sq = (*move_x * *move_x) + (*move_y * *move_y);
	if (len_sq > 0)
	{
		normalized_speed = 1.0 / sqrt(len_sq);
		*move_x *= normalized_speed;
		*move_y *= normalized_speed;
	}
}

void	handle_movement_xy(t_game *game, float speed)
{
	t_fvec	move;
	t_fvec	new_pos;

	if (!game->state[S_UP] && !game->state[S_DOWN]
		&& !game->state[S_LEFT] && !game->state[S_RIGHT])
		return ;
	move.x = 0;
	move.y = 0;
	calculate_movement(game, &move.x, &move.y);
	normalize_movement(&move.x, &move.y);
	new_pos.x = game->player.pos.x + move.x * speed;
	new_pos.y = game->player.pos.y + move.y * speed;
	check_collision(&game->player.pos, new_pos, PLAYER_RADIUS, game);
}

void	handle_movement(t_game *game)
{
	int	run_speed;

	if (game->state[S_CAUGHT])
		return ;
	run_speed = 1;
	if (game->state[S_RUN] == 1)
	{
		game->state[S_MAP_BIG] = 0;
		run_speed = RUN_SPD;
	}
	handle_movement_xy(game, PLAYER_SPD * game->frame.time * run_speed);
	handle_pitch(game);
	handle_yaw(game, ROT_SPD * game->frame.time,
		game->player.dir.x, game->player.plane.x);
}
