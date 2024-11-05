/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_ui.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:09:36 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/05 19:15:54 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	display_fps_counter(t_game *game)
{
	if (game->frame.fps_str)
	{
		mlx_string_put(game->mlx, game->win, 4, 13, WHITE, game->frame.fps_str);
		mlx_string_put(game->mlx, game->win, 20, 13, WHITE, "FPS");
	}
	else
		mlx_string_put(game->mlx, game->win, 4, 13, WHITE,
			"INITIALIZING FPS...");
}

void	display_msg(t_game *game)
{
	if (game->state[S_MOUSE] == 0)
		mlx_string_put(game->mlx, game->win, 4, 26, WHITE,
			"MOUSE DISABLED, [CLICK ANYWHERE] to enable");
	else
		mlx_string_put(game->mlx, game->win, 4, 26, WHITE,
			"MOUSE ENABLED, [P] to disable");
	mlx_string_put(game->mlx, game->win, 4, 39, WHITE,
		"[WSAD] or [ARROW KEYS] to move, [SHIFT] to run");
}

void	display_pause_screen(t_game *game)
{
	if (!game->state[S_PAUSE])
		return ;
	put_img((t_vec){0, 0}, &game->img[T_PAUSE], &game->img[T_WIN]);
	mlx_put_image_to_window(game->mlx, game->win, game->img[T_WIN].img, 0, 0);
}
