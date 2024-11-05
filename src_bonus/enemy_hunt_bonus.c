/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_hunt_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 07:08:47 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/05 19:45:13 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D_bonus.h"

static int	d100(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_usec + 42) ^ 42) % 100);
}

void	move_enemy_cardinal(t_game *game, int direction, t_fvec *new_pos)
{
	t_vec	step_dir;

	step_dir.x = 0;
	step_dir.y = 0;
	if (direction == S_UP)
		step_dir.y = -1;
	else if (direction == S_DOWN)
		step_dir.y = 1;
	else if (direction == S_LEFT)
		step_dir.x = -1;
	else if (direction == S_RIGHT)
		step_dir.x = 1;
	new_pos->x = game->enemy.pos.x + step_dir.x * ENEMY_SPD * game->frame.time;
	new_pos->y = game->enemy.pos.y + step_dir.y * ENEMY_SPD * game->frame.time;
}

void	move_enemy_diagonal(t_game *game, int direction, t_fvec *new_pos)
{
	t_vec	step_dir;

	step_dir.x = 0;
	step_dir.y = 0;
	if (direction == UP_LEFT || direction == UP_RIGHT)
	{
		step_dir.x = -1;
		step_dir.y = -1;
		if (direction == UP_RIGHT)
			step_dir.x = 1;
	}
	else if (direction == DOWN_LEFT || direction == DOWN_RIGHT)
	{
		step_dir.x = -1;
		step_dir.y = 1;
		if (direction == DOWN_RIGHT)
			step_dir.x = 1;
	}
	new_pos->x = game->enemy.pos.x + step_dir.x * ENEMY_SPD * game->frame.time;
	new_pos->y = game->enemy.pos.y + step_dir.y * ENEMY_SPD * game->frame.time;
}

void	move_enemy(t_game *game, t_fvec *new_pos)
{
	if (game->enemy.move_seed >= 0 && game->enemy.move_seed <= 12)
		move_enemy_cardinal(game, S_UP, new_pos);
	else if (game->enemy.move_seed >= 13 && game->enemy.move_seed <= 25)
		move_enemy_cardinal(game, S_DOWN, new_pos);
	else if (game->enemy.move_seed >= 26 && game->enemy.move_seed <= 38)
		move_enemy_cardinal(game, S_LEFT, new_pos);
	else if (game->enemy.move_seed >= 39 && game->enemy.move_seed <= 51)
		move_enemy_cardinal(game, S_RIGHT, new_pos);
	else if (game->enemy.move_seed >= 52 && game->enemy.move_seed <= 63)
		move_enemy_diagonal(game, UP_LEFT, new_pos);
	else if (game->enemy.move_seed >= 64 && game->enemy.move_seed <= 75)
		move_enemy_diagonal(game, UP_RIGHT, new_pos);
	else if (game->enemy.move_seed >= 76 && game->enemy.move_seed <= 87)
		move_enemy_diagonal(game, DOWN_LEFT, new_pos);
	else
		move_enemy_diagonal(game, DOWN_RIGHT, new_pos);
}

void	enemy_hunt(t_game *game)
{
	t_fvec	new_pos;

	if (game->enemy.move_seed == 0)
		game->enemy.move_seed = d100();
	else
	{
		if (delay_ms(game->enemy.move_inc, &game->timer[TIMER_ENEMY]))
		{
			game->enemy.move_inc += 1000;
			game->enemy.move_seed = d100();
		}
	}
	move_enemy(game, &new_pos);
	if (check_collision(&game->enemy.pos, new_pos, ENEMY_RADIUS, game))
	{
		game->enemy.move_seed = 0;
		game->enemy.move_inc = 0;
	}
	if (d100() == 1)
		enemy_open_door(game);
}
