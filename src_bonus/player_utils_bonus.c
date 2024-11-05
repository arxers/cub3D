/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 07:58:37 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/05 19:43:03 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D_bonus.h"

int	out_of_bounds(t_fvec map, t_game *game)
{
	if (map.x < 0 || map.y < 0 || map.x >= game->map.size.x
		|| map.y >= game->map.size.y)
		return (1);
	return (0);
}

// Unstucks the player by pushing them,
// if it's radius would be within a door after one closes.
void	unstuck_player(t_game *game, t_ray r)
{
	t_vec	pos;

	pos.x = (int)game->player.pos.x - (int)r.map.x;
	pos.y = (int)game->player.pos.y - (int)r.map.y;
	if (pos.x == -1)
		game->player.pos = (t_fvec){game->player.pos.x - PLAYER_RADIUS,
			game->player.pos.y};
	if (pos.x == 1)
		game->player.pos = (t_fvec){game->player.pos.x + PLAYER_RADIUS,
			game->player.pos.y};
	if (pos.y == -1)
		game->player.pos = (t_fvec){game->player.pos.x, game->player.pos.y
			- PLAYER_RADIUS};
	if (pos.y == 1)
		game->player.pos = (t_fvec){game->player.pos.x, game->player.pos.y
			+ PLAYER_RADIUS};
}

int	check_collision(t_fvec *pos, t_fvec new_pos, float radius, t_game *game)
{
	t_fvec	side;
	int		collision;

	collision = 0;
	if (new_pos.x - pos->x < 0)
		side.x = -radius;
	else
		side.x = radius;
	if (new_pos.y - pos->y < 0)
		side.y = -radius;
	else
		side.y = radius;
	if (game->map.arr[(int)(pos->y)][(int)(new_pos.x - radius)] < 1
		&& game->map.arr[(int)(pos->y - radius)][(int)(new_pos.x + side.x)] < 1
		&& game->map.arr[(int)(pos->y + radius)][(int)(new_pos.x + side.x)] < 1)
		pos->x = new_pos.x;
	else
		collision = 1;
	if (game->map.arr[(int)(new_pos.y - radius)][(int)(pos->x)] < 1
		&& game->map.arr[(int)(new_pos.y + side.y)][(int)(pos->x - radius)] < 1
		&& game->map.arr[(int)(new_pos.y + side.y)][(int)(pos->x + radius)] < 1)
		pos->y = new_pos.y;
	else
		collision = 1;
	return (collision);
}
