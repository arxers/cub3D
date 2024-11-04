/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 07:20:58 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/04 07:21:15 by jaslim           ###   ########.fr       */
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

void	init_enemy(t_game *game)
{
	game->enemy.pos.x = game->scene.pos_xeno.x + 0.5;
	game->enemy.pos.y = game->scene.pos_xeno.y + 0.5;
	game->enemy.frame = T_XENO0;
	game->enemy.img = game->img[T_XENO0];
}

void	init_items(t_game *game)
{
	int	x;
	int	y;
	int	i;

	game->item.count = count_tile(game, -3);
	game->item.arr = ft_calloc(game->item.count, sizeof(t_coin));
	i = 0;
	y = 0;
	while (y < game->map.size.y - 1)
	{
		x = 0;
		while (x < game->map.size.x - 1)
		{
			if (game->map.arr[y][x] == -3)
			{
				game->item.arr[i].pos.x = (float)x + 0.5;
				game->item.arr[i].pos.y = (float)y + 0.5;
				i++;
				if (i == game->item.count)
					return ;
			}
			x++;
		}
		y++;
	}
}

void	init_pwl(t_game *game)
{
	game->pwl.item.pos.x = game->scene.pos_powerloader.x + 0.5;
	game->pwl.item.pos.y = game->scene.pos_powerloader.y + 0.5;
	game->pwl.overlay_img = game->img[T_PWL_ARM0];
	game->pwl.frame = T_PWL_ARM0;
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
	init_enemy(game);
	init_items(game);
	init_pwl(game);
	game->light.min = 0.25;
	game->light.max = 2.5;
	game->light.ambient = 0.15;
	game->win = mlx_new_window(game->mlx, RES_X, RES_Y, "cub3D");
	if (game->win == NULL)
		return (1);
	mlx_mouse_move(game->mlx, game->win, RES_X2, RES_Y2);
	return (0);
}
