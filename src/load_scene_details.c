/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene_details.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:18:14 by jsu               #+#    #+#             */
/*   Updated: 2024/11/04 13:18:17 by jsu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/validate_input.h"

int	load_scene_details(int map_fd, t_scene **scene)
{
	char	*line;
	int		res;

	line = get_next_line(map_fd);
	while (line)
	{
		if (is_all_six_scene_details_present(*scene) == 0)
		{
			if (load_map_buffer(line, map_fd, scene) == -1)
			{
				ft_putstr_fd("Error\nCannot load map\n", 2);
				return (-1);
			}
			return (0);
		}
		res = load_scene_details_to_struct(&line, map_fd, scene);
		if (res == 1)
			continue ;
		else if (res == -1)
			return (-1);
		free(line);
		line = get_next_line(map_fd);
	}
	return (0);
}

/*
only if ALL of the six details are present, then return 0 (success)
else return -1 (error; one or more of the details are missing)
*/
int	is_all_six_scene_details_present(t_scene *scene)
{
	if ((scene->no != NULL)
		&& (scene->so != NULL)
		&& (scene->ea != NULL)
		&& (scene->we != NULL)
		&& (scene->floor != NULL)
		&& (scene->ceiling != NULL))
		return (0);
	else
		return (-1);
}

/*
only reach here when prev six details are preliminarily loaded to 'scene' struct

continue to read line by line, with gnl()
NOTE. used safe_strjoin(), instead of ft_strjoin() to sidestep unfreed s1 param
if cannot safe_strjoin() fails:
	print errmsg to stderr
	flush gnl buffer, and close fd
	return -1 (error)
else
	close fd
	return 0 (success)
*/
int	load_map_buffer(char *line, int map_fd, t_scene **scene)
{
	while (line)
	{
		(*scene)->tmp_map_buf = safe_strjoin((*scene)->tmp_map_buf, line);
		if ((*scene)->tmp_map_buf == NULL)
		{
			ft_putstr_fd("Error\nCannot load map section)\n", 2);
			flush_gnl(&line, map_fd);
			return (-1);
		}
		free(line);
		line = get_next_line(map_fd);
	}	
	close(map_fd);
	return (0);
}

void	flush_gnl(char **line, int map_fd)
{
	if (*line)
		free(*line);
	get_next_line(-1);
	close(map_fd);
	*line = NULL;
}
