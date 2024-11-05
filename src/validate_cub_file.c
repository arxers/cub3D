/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cub_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:59:58 by jsu               #+#    #+#             */
/*   Updated: 2024/11/05 18:27:52 by jaslim           ###   ########.fr       */
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
		ft_putstr_fd("Usage: cub3D [*.cub]\n", 2);
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

void	free_scene_struct(t_scene *s)
{
	if (s->no != NULL)
		free(s->no);
	if (s->so != NULL)
		free(s->so);
	if (s->ea != NULL)
		free(s->ea);
	if (s->we != NULL)
		free(s->we);
	if (s->floor != NULL)
		free(s->floor);
	if (s->ceiling != NULL)
		free(s->ceiling);
	if (s->tmp_map_buf != NULL)
		free(s->tmp_map_buf);
	if (s->map != NULL)
		free_char_map(s->map);
	if (s->map_bak != NULL)
		free_char_map(s->map_bak);
}
