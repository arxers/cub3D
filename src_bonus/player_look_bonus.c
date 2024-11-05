/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_look_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 07:00:26 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/05 19:43:11 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D_bonus.h"

void	vertical_look(t_game *game, float delta)
{
	const int	limit = RES_Y2;
	int			new;

	new = game->player.pitch + delta;
	if (new >= -limit && new <= limit)
		game->player.pitch += delta;
	if (game->player.pitch < -limit)
		game->player.pitch = -limit;
	else if (game->player.pitch > limit)
		game->player.pitch = limit;
}

void	handle_mouselook(t_game *game)
{
	const t_vec	center = {RES_X2, RES_Y2};
	t_vec		mouse;
	float		old_dir_x;
	float		old_plane_x;
	t_vec		delta;

	mlx_mouse_get_pos(game->mlx, game->win, &mouse.x, &mouse.y);
	delta.x = mouse.x - center.x;
	delta.y = mouse.y - center.y;
	if (delta.x != 0 || delta.y != 0)
	{
		old_dir_x = game->player.dir.x;
		old_plane_x = game->player.plane.x;
		game->player.dir.x = game->player.dir.x * cos(MOUSE_SEN * delta.x)
			- game->player.dir.y * sin(MOUSE_SEN * delta.x);
		game->player.dir.y = old_dir_x * sin(MOUSE_SEN * delta.x)
			+ game->player.dir.y * cos(MOUSE_SEN * delta.x);
		game->player.plane.x = game->player.plane.x * cos(MOUSE_SEN * delta.x)
			- game->player.plane.y * sin(MOUSE_SEN * delta.x);
		game->player.plane.y = old_plane_x * sin(MOUSE_SEN * delta.x)
			+ game->player.plane.y * cos(MOUSE_SEN * delta.x);
		vertical_look(game, delta.y);
		mlx_mouse_move(game->mlx, game->win, center.x, center.y);
	}
}

void	handle_yaw(t_game *game, float speed, float old_dir_x,
	float old_plane_x)
{
	if (game->state[S_ROT_L] && game->state[S_ROT_R])
		return ;
	if (game->state[S_ROT_L])
	{
		game->player.dir.x = game->player.dir.x * cos(-speed)
			- game->player.dir.y * sin(-speed);
		game->player.dir.y = old_dir_x * sin(-speed)
			+ game->player.dir.y * cos(-speed);
		game->player.plane.x = game->player.plane.x
			* cos(-speed) - game->player.plane.y * sin(-speed);
		game->player.plane.y = old_plane_x * sin(-speed)
			+ game->player.plane.y * cos(-speed);
	}
	else if (game->state[S_ROT_R])
	{
		game->player.dir.x = game->player.dir.x * cos(speed)
			- game->player.dir.y * sin(speed);
		game->player.dir.y = old_dir_x * sin(speed)
			+ game->player.dir.y * cos(speed);
		game->player.plane.x = game->player.plane.x * cos(speed)
			- game->player.plane.y * sin(speed);
		game->player.plane.y = old_plane_x * sin(speed)
			+ game->player.plane.y * cos(speed);
	}
}

void	handle_pitch(t_game *game)
{
	const int	limit = RES_Y2;

	if (game->state[S_ROT_U] && game->state[S_ROT_D])
		return ;
	if (game->state[S_ROT_U])
		game->player.pitch -= game->frame.time;
	else if (game->state[S_ROT_D])
		game->player.pitch += game->frame.time;
	if (game->player.pitch < -limit)
		game->player.pitch = -limit;
	else if (game->player.pitch > limit)
		game->player.pitch = limit;
}
