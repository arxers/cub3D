/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene_details_to_struct_bonus.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:25:36 by jsu               #+#    #+#             */
/*   Updated: 2024/11/05 19:44:11 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/validate_input_bonus.h"

/*
read map.cub line by line, with gnl()
(if) 6 scene details are loaded
	load remainder of map.cub file to a (char *)tmp_map_buf, in 'scene' struct
(if) current line is "empty"
	move to next line
(else if) current line, starts with expected id & is first (not a duplicate)
	then assign detail to t_scene struct
(else)
	err msg, flush_gnl(), return (-1)

*/

int	load_scene_details_to_struct(char **line, int map_fd, t_scene **scene)
{
	if (ft_strcmp(*line, "\n") == 0)
	{
		free(*line);
		*line = get_next_line(map_fd);
		return (1);
	}
	else if (is_start_with_expected_identifier(*line) == 0 && \
		is_first_detail(*line, *scene) == 0)
	{
		assign_wall_to_scene_struct(*line, scene);
		assign_f_or_c_to_scene_struct(*line, scene);
		return (0);
	}
	else
	{
		ft_putstr_fd("Error\nProblem with line for scene details\n", 2);
		flush_gnl(line, map_fd);
		return (-1);
	}		
}

/*
if line starts with any one of the six possible identifiers, return 0 (success)
else return -1 (error, line does NOT start with an expected identifier)
*/
int	is_start_with_expected_identifier(char *s)
{
	if (!ft_strncmp(s, "NO ", 3)
		|| !ft_strncmp(s, "SO ", 3)
		|| !ft_strncmp(s, "EA ", 3)
		|| !ft_strncmp(s, "WE ", 3)
		|| !ft_strncmp(s, "F ", 2)
		|| !ft_strncmp(s, "C ", 2))
		return (0);
	else
		return (-1);
}

/*
checks whether a specific scene detail (char *s), is the first to be loaded into
the t_scene struct

if yes, return (0), for success, 
else return (-1) for failure
*/
int	is_first_detail(char *s, t_scene *scene)
{
	if ((ft_strncmp(s, "NO ", 3) == 0 && scene->no == NULL) || \
		(ft_strncmp(s, "SO ", 3) == 0 && scene->so == NULL) || \
		(ft_strncmp(s, "EA ", 3) == 0 && scene->ea == NULL) || \
		(ft_strncmp(s, "WE ", 3) == 0 && scene->we == NULL) || \
		(ft_strncmp(s, "F ", 2) == 0 && scene->floor == NULL) || \
		(ft_strncmp(s, "C ", 2) == 0 && scene->ceiling == NULL))
		return (0);
	return (-1);
}

/*
if line starts with expected identifier AND detail is still empty in struct
then assign detail to 'scene' struct

if line starts with expected identifier, BUT detail is already filled in struct
then error out, return (-1)
*/
int	assign_wall_to_scene_struct(char *s, t_scene **scene)
{
	if (ft_strncmp(s, "NO ", 3) == 0 && (*scene)->no == NULL)
	{
		(*scene)->no = ft_strdup(s);
		return (0);
	}
	else if (ft_strncmp(s, "SO ", 3) == 0 && (*scene)->so == NULL)
	{
		(*scene)->so = ft_strdup(s);
		return (0);
	}
	else if (ft_strncmp(s, "EA ", 3) == 0 && (*scene)->ea == NULL)
	{
		(*scene)->ea = ft_strdup(s);
		return (0);
	}
	else if (ft_strncmp(s, "WE ", 3) == 0 && (*scene)->we == NULL)
	{
		(*scene)->we = ft_strdup(s);
		return (0);
	}
	return (-1);
}

int	assign_f_or_c_to_scene_struct(char *s, t_scene **scene)
{
	if (ft_strncmp(s, "F ", 2) == 0 && (*scene)->floor == NULL)
	{
		(*scene)->floor = ft_strdup(s);
		return (0);
	}
	else if (ft_strncmp(s, "C ", 2) == 0 && (*scene)->ceiling == NULL)
	{
		(*scene)->ceiling = ft_strdup(s);
		return (0);
	}
	return (-1);
}
