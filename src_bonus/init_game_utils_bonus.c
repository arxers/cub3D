/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 07:22:04 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/05 19:44:57 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D_bonus.h"

void	init_player_dir(t_game *game)
{
	char	c;

	c = game->scene.map[game->scene.p_pos.y][game->scene.p_pos.x];
	if (c == 'N')
	{
		game->player.dir.x = 0;
		game->player.dir.y = -1;
	}
	else if (c == 'S')
	{
		game->player.dir.x = 0;
		game->player.dir.y = 1;
	}
	else if (c == 'E')
	{
		game->player.dir.x = 1;
		game->player.dir.y = 0;
	}
	else if (c == 'W')
	{
		game->player.dir.x = -1;
		game->player.dir.y = 0;
	}
}

int	count_tile(t_game *game, int n)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (y < game->map.size.y - 1)
	{
		x = 0;
		while (x < game->map.size.x - 1)
		{
			if (game->map.arr[y][x] == n)
				count++;
			x++;
		}
		y++;
	}
	(void)game;
	return (count);
}
