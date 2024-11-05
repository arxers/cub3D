/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_specials_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 07:32:15 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/05 19:44:28 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D_bonus.h"

void	pause_game(t_game *game)
{
	t_vec	center;

	center.x = RES_X2;
	center.y = RES_Y2;
	if (game->state[S_RUN])
		game->state[S_PAUSE] = !game->state[S_PAUSE];
	if (!game->state[S_PAUSE] && game->state[S_MOUSE])
		mlx_mouse_move(game->mlx, game->win, center.x, center.y);
}

void	toggle_mouse(t_game *game)
{
	t_vec	center;

	center.x = RES_X2;
	center.y = RES_Y2;
	if (game->state[S_MOUSE] == 0)
		mlx_mouse_move(game->mlx, game->win, center.x, center.y);
	game->state[S_MOUSE] = !game->state[S_MOUSE];
}

int	exit_game(t_game *game)
{
	cleanup(game, 0, "exit\n");
	return (0);
}
