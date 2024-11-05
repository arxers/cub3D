/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 06:58:49 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/05 19:44:49 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D_bonus.h"

// Displays a button prompt at the center of the screen.
void	display_ui_msg(t_game *game, char *key, char *msg)
{
	int	msg_y;

	msg_y = 0;
	if (key)
		msg_y = 15;
	draw_circle_outline(&game->img[T_WIN],
		(t_vec){RES_X2, RES_Y2}, 25, WHITE);
	if (key)
		mlx_string_put(game->mlx, game->win, RES_X2 + 34,
			RES_Y2, WHITE, key);
	mlx_string_put(game->mlx, game->win, RES_X2 + 34,
		RES_Y2 + msg_y, WHITE, msg);
}

void	interact_door(t_game *game, t_ray r)
{
	game->map.arr[(int)r.map.y][(int)r.map.x]
		= -game->map.arr[(int)r.map.y][(int)r.map.x];
	if (r.wall_dist <= PLAYER_RADIUS)
		unstuck_player(game, r);
	game->state[S_INTERACT] = 0;
	game->map.update = 1;
}

void	interact_pwl(t_game *game)
{
	if (game->item.collected < REQUIRED_ITEMS)
		return ;
	game->map.arr[(int)game->pwl.item.pos.y][(int)game->pwl.item.pos.x] = 0;
	game->player.pos = game->pwl.item.pos;
	game->player.dir.x = -0.7071;
	game->player.dir.y = 0.7071;
	game->player.plane.x = -game->player.dir.y * 0.66;
	game->player.plane.y = game->player.dir.x * 0.66;
	game->player.z = 0.3;
	game->player.pitch = 100;
	game->pwl.item.collected = 1;
	game->map.update = 1;
}

void	check_interact(t_game *game, int *tile_hit, t_ray *r)
{
	set_ray_direction(game, r, 0, 0);
	set_ray_step_direction(game, r);
	*tile_hit = dda_interact(r, game);
	if (*tile_hit == 0)
		return ;
	if (r->side == VERTICAL)
		r->wall_dist = r->side_dist.x - r->delta_dist.x;
	else
		r->wall_dist = r->side_dist.y - r->delta_dist.y;
	if (r->wall_dist < 2.0 && !game->state[S_MAP_BIG])
	{
		if (*tile_hit == TILE_DOOR || *tile_hit == TILE_DOOR_OPEN)
			display_ui_msg(game, "[E]", UI_DOOR);
		if (*tile_hit == TILE_PWL)
		{
			if (game->item.collected < REQUIRED_ITEMS)
				display_ui_msg(game, NULL, UI_PWL_FALSE);
			else
				display_ui_msg(game, "[E]", UI_PWL_TRUE);
		}
	}
}

void	interact(t_game *game)
{
	t_ray	r;
	int		tile_hit;

	check_interact(game, &tile_hit, &r);
	if (game->state[S_INTERACT] == 1)
	{
		if (tile_hit == TILE_DOOR || tile_hit == TILE_DOOR_OPEN)
			return (interact_door(game, r));
		if (tile_hit == TILE_PWL)
			interact_pwl(game);
	}
}
