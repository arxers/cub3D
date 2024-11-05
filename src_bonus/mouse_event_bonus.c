/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 06:45:17 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/05 19:43:13 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D_bonus.h"

int	mwheel(unsigned int key, t_game *game)
{
	const float	step = 0.1;
	const int	limit = RES_Y2;

	if (key == 4 && game->player.zoom < 1.8)
	{
		game->player.zoom += step;
		if (game->player.pitch != limit && game->player.pitch != -limit)
			game->player.pitch *= game->player.zoom
				/ (game->player.zoom - step);
	}
	else if (key == 5 && game->player.zoom > 1)
	{
		game->player.zoom -= step;
		if (game->player.pitch != limit && game->player.pitch != -limit)
			game->player.pitch *= game->player.zoom
				/ (game->player.zoom + step);
		if (game->player.pitch > limit)
			game->player.pitch = limit;
		else if (game->player.pitch < -limit)
			game->player.pitch = -limit;
	}
	return (0);
}

int	mouse_event(unsigned int key, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (game->state[S_CAUGHT])
		return (0);
	if (key == 1)
	{
		if (game->state[S_MOUSE] == 0)
		{
			mlx_mouse_move(game->mlx, game->win, RES_X2, RES_Y2);
			game->state[S_MOUSE] = 1;
		}
		if (game->pwl.item.collected && game->state[S_MOUSE])
			game->state[S_PUNCHING] = 1;
	}
	return (mwheel(key, game));
}
