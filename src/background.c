/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:16:26 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/04 23:24:33 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	init_bg(t_game *game, int ceiling, int floor)
{
	t_vec	size;

	size.x = RES_X;
	size.y = RES_Y;
	if (init_img(game->mlx, &game->img[T_CEILING], RES_X, RES_Y) == -1
		|| init_img(game->mlx, &game->img[T_FLOOR], RES_X, RES_Y) == -1)
		return (-1);
	draw_rectangle(&game->img[T_CEILING], (t_vec){0, 0}, size, ceiling);
	draw_rectangle(&game->img[T_FLOOR], (t_vec){0, 0}, size, floor);
	return (0);
}

void	draw_bg(t_game *game)
{
	put_img((t_vec){0, 0}, &game->img[T_CEILING], &game->img[T_WIN]);
	put_img((t_vec){0, RES_Y2 - game->player.pitch}, &game->img[T_FLOOR],
		&game->img[T_WIN]);
}
