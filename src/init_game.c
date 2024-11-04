/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 07:20:58 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/04 23:20:22 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	init_player(t_game *game)
{
	init_player_dir(game);
	game->player.pos.x = game->scene.p_pos.x + 0.5;
	game->player.pos.y = game->scene.p_pos.y + 0.5;
	game->player.plane.x = -game->player.dir.y * 0.66;
	game->player.plane.y = game->player.dir.x * 0.66;
	game->player.zoom = 1.0;
}

int	init_game(t_game *game, t_scene scene)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return (1);
	mlx_do_key_autorepeatoff(game->mlx);
	if (init_img(game->mlx, &game->img[T_WIN], RES_X, RES_Y) == -1)
		return (2);
	if (init_minimap(game, scene.map_dim) == -1
		|| init_bg(game, scene.hex_ceiling, scene.hex_floor) == -1)
		return (2);
	if (load_xpms(game))
		return (3);
	game->frame.time = 1000.0 / TARGET_FPS;
	gettimeofday(&game->frame.last, NULL);
	init_player(game);
	game->win = mlx_new_window(game->mlx, RES_X, RES_Y, "cub3D");
	if (game->win == NULL)
		return (1);
	mlx_mouse_move(game->mlx, game->win, RES_X2, RES_Y2);
	return (0);
}
