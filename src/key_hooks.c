/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 07:28:56 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/04 23:30:04 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	handle_keystate(unsigned int key, int state, t_game *game)
{
	if (key == XK_Up || key == XK_w)
		game->state[S_UP] = state;
	if (key == XK_Down || key == XK_s)
		game->state[S_DOWN] = state;
	if (key == XK_a)
		game->state[S_LEFT] = state;
	if (key == XK_d)
		game->state[S_RIGHT] = state;
	if (key == XK_r)
		game->state[S_ROT_U] = state;
	if (key == XK_f)
		game->state[S_ROT_D] = state;
	if (key == XK_Left)
		game->state[S_ROT_L] = state;
	if (key == XK_Right)
		game->state[S_ROT_R] = state;
	if (key == XK_Shift_L)
		game->state[S_RUN] = state;
	if (key == XK_Control_L)
		game->state[S_SPACE] = state;
	if (key == XK_e)
		game->state[S_INTERACT] = state;
}

int	key_press(unsigned int key, t_game *game)
{
	handle_keystate(key, 1, game);
	if (key == XK_Tab)
		pause_game(game);
	if (key == XK_Escape)
		exit_game(game);
	if (key == XK_p)
		toggle_mouse(game);
	if (key == XK_m)
		game->state[S_MAP_DISABLE] = !game->state[S_MAP_DISABLE];
	if (key == XK_1)
	{
		game->state[S_MAP_DISABLE] = 0;
		game->state[S_MAP_BIG] = !game->state[S_MAP_BIG];
	}
	return (0);
}

int	key_release(unsigned int key, t_game *game)
{
	handle_keystate(key, 0, game);
	return (0);
}
