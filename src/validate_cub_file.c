/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cub_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:59:58 by jsu               #+#    #+#             */
/*   Updated: 2024/11/04 13:00:04 by jsu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/validate_input.h"

/* 
check num of cmdline args
if argc != 2, return -1 (error)
else return 0
*/
int	check_n_cmdline_args(int ac)
{
	if (ac != 2)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		ft_putstr_fd("Error\nUsage: cub3D [*.cub]\n", 2);
		return (-1);
	}
	return (0);
}

/* 
check if map ends with ".cub"
if <map file> ends in ".cub", return 0
else return -1
*/
int	is_map_a_dot_cub_file(char *s)
{
	int	len;

	len = ft_strlen(s);
	if ((s[len - 1] == 'b') && \
		(s[len - 2] == 'u') && \
		(s[len - 3] == 'c') && \
		(s[len - 4] == '.') \
		)
		return (0);
	else
	{
		ft_putstr_fd("Error\nMap does not end in .cub\n", 2);
		return (-1);
	}
}

/*
if file can be opened, then return 0
else return -1
*/
int	is_map_file_openable(char *mapfile)
{
	int	map_fd;

	map_fd = open(mapfile, O_RDONLY);
	if (map_fd == -1)
	{
		ft_putstr_fd("Error\nMap cannot be opened\n", 2);
		return (-1);
	}
	close(map_fd);
	return (0);
}

/* 
NOTE. load_bonus_scene() differs from load_mandatory_scene() 
for TWO function calls

BONUS / MANDATORY
is_bonus_map_char_valid()	/ is map_char_valid()
is_bonus_map_valid()		/ is_mandatory_map_char_valid()

key difference is that in the bonus versions, they consider FOUR extra chars:
C, D, X, P
*/
int	load_bonus_scene(char *mapfile, t_scene *scene)
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
	if (is_bonus_map_char_valid(scene->tmp_map_buf) == -1 || \
		process_map(scene) == -1 || \
		is_bonus_map_valid(scene) == -1)
		return (-1);
	return (0);
}
