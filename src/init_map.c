/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 07:38:40 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/05 22:17:27 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	convert_row_to_ints(int *output_row, char *input_row)
{
	int	x;

	x = 0;
	while (input_row[x])
	{
		if (input_row[x] == '1')
			output_row[x] = 1;
		else if (input_row[x] == 'D')
			output_row[x] = 2;
		else if (input_row[x] == 'P')
			output_row[x] = 3;
		else if (input_row[x] == 'C')
			output_row[x] = -3;
		else
			output_row[x] = 0;
		x++;
	}
}

int	**char_to_int_map(char **input)
{
	t_vec	it;
	int		num_strings;
	int		**output;

	num_strings = ft_count_strings(input);
	output = ft_calloc(num_strings, sizeof(int *));
	if (!output)
		return (NULL);
	it.y = 0;
	while (it.y < num_strings)
	{
		output[it.y] = ft_calloc(ft_strlen(input[it.y]), sizeof(int));
		if (!output[it.y])
		{
			free_int_array(output, it.y);
			return (NULL);
		}
		convert_row_to_ints(output[it.y], input[it.y]);
		it.y++;
	}
	return (output);
}

int	init_minimap(t_game *game, t_vec map_grid_size)
{
	t_vec	map;
	t_vec	mask;

	map.x = map_grid_size.x * MAP_CELL_SIZE;
	map.y = map_grid_size.y * MAP_CELL_SIZE;
	mask.x = 16 * MAP_CELL_SIZE * 0.5;
	mask.y = 16 * MAP_CELL_SIZE * 0.5;
	if (init_img(game->mlx, &game->img[T_MAP], map.x, map.y) == -1
		|| init_img(game->mlx, &game->img[T_MAP_TILES], map.x, map.y) == -1
		|| init_img(game->mlx, &game->img[T_MAP_MASK], mask.x, mask.y) == -1
		|| init_img(game->mlx, &game->img[T_MAP_BG], mask.x, mask.y) == -1)
		return (-1);
	game->map.arr = char_to_int_map(game->scene.map);
	game->map.size.x = game->scene.map_dim.x;
	game->map.size.y = game->scene.map_dim.y;
	game->map.offset.x = RES_X2 - game->img[T_MAP_MASK].size.x * 0.5;
	game->map.offset.y = RES_Y - game->img[T_MAP_MASK].size.x - MAP_CELL_SIZE;
	draw_rectangle(&game->img[T_MAP_BG], (t_vec){0, 0},
		game->img[T_MAP_MASK].size, BLACK);
	draw_diagonal_lines(&game->img[T_MAP_BG],
		game->img[T_MAP_MASK].size, 0x333333);
	update_map_tiles(game);
	return (0);
}
