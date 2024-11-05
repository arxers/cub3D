/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:20:28 by jsu               #+#    #+#             */
/*   Updated: 2024/11/05 18:44:17 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/validate_input.h"

int	load_scene(char *mapfile, t_scene *scene)
{
	int		map_fd;

	map_fd = open(mapfile, O_RDONLY);
	if (map_fd == -1)
	{
		ft_putstr_fd("Error\nMap cannot be opened\n", 2);
		return (-1);
	}
	if (load_scene_details(map_fd, &scene) == -1 || prepare_walls(&scene) == -1
		|| is_six_details_valid(scene) == -1)
		return (-1);
	scene->hex_floor = convert_rgb_array_to_int(scene->floor);
	scene->hex_ceiling = convert_rgb_array_to_int(scene->ceiling);
	if (is_map_char_valid(scene->tmp_map_buf) == -1 || \
		process_map(scene) == -1 || \
		is_map_valid(scene) == -1)
		return (-1);
	return (0);
}

int	is_map_char_valid(char *s)
{
	const char	ref[] = " \n10NSEW";
	int			i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(ref, s[i]) == NULL)
		{
			ft_putstr_fd("Error\nInvalid map char\n", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	is_map_valid(t_scene *scene)
{
	if (is_num_player_valid(scene->map) == -1 || \
		load_player_pos(scene->map, scene) == -1)
		return (-1);
	ff_mandatory(scene->p_pos.y, scene->p_pos.x, scene);
	if (is_fill_char_at_map_border(scene) == 0)
		return (-1);
	return (0);
}

/*
NOTE. ff is short for flood fill

if out of bounds row-wise, return
if out of bounds col-wise, return
if char at current pos: is wall '1', or fill 'F', return
if char at current pos: is empty '0', or valid (player) char, replace with 'F'
try to ff() the four cardinal directions, relative to current char pos
*/
void	ff_mandatory(int i, int j, t_scene *s)
{
	if (i < 0 || i > s->map_dim.y - 1)
		return ;
	if (j < 0 || j > s->map_dim.x - 1)
		return ;
	if (s->map_bak[i][j] == '1' || s->map_bak[i][j] == 'F')
		return ;
	if (s->map_bak[i][j] == '0' || ft_strchr("NSEW", s->map_bak[i][j]))
		s->map_bak[i][j] = 'F';
	ff_mandatory(i + 1, j, s);
	ff_mandatory(i - 1, j, s);
	ff_mandatory(i, j + 1, s);
	ff_mandatory(i, j - 1, s);
}
