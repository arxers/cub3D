/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:36:02 by jsu               #+#    #+#             */
/*   Updated: 2024/11/04 13:36:06 by jsu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/validate_input.h"

/* 
wrapper + retval check for prepare_a_wall()
*/
int	prepare_walls(t_scene **scene)
{
	(*scene)->no = prepare_a_wall((*scene)->no);
	(*scene)->so = prepare_a_wall((*scene)->so);
	(*scene)->ea = prepare_a_wall((*scene)->ea);
	(*scene)->we = prepare_a_wall((*scene)->we);
	(*scene)->floor = prepare_a_wall((*scene)->floor);
	(*scene)->ceiling = prepare_a_wall((*scene)->ceiling);
	if ((*scene)->no == NULL || \
		(*scene)->so == NULL || \
		(*scene)->ea == NULL || \
		(*scene)->we == NULL || \
		(*scene)->floor == NULL || \
		(*scene)->ceiling == NULL)
	{
		ft_putstr_fd("Error\nProblem with scene details\n", 2);
		return (-1);
	}
	return (0);
}

/* 
ft_split the line that begins with the expected identifiers at start of line
replace the last char, should be a '\n' char, with '\0'
this will handle the case where ft_split "xxx"<space>'\n', returns 3 rows

ensure that the ft_split result only has 2 rows! with ft_count_strings()
ft_strdup, the second array from the ft_split result
	
credits to @filim, for helping me "over the hump"!
*/
char	*prepare_a_wall(char *s)
{
	char	**arr;
	char	*tmp;

	s[ft_strlen(s) - 1] = '\0';
	arr = ft_split(s, ' ');
	if (!arr)
		return (NULL);
	free(s);
	if (ft_count_strings(arr) != 2)
	{
		free_char_map(arr);
		return (NULL);
	}
	tmp = ft_strdup(arr[1]);
	if (!tmp)
		return (NULL);
	free_char_map(arr);
	return (tmp);
}

void	free_char_map(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/*
checks if:
FOUR wall textures, end in ".xpm"
TWO colors, are 3 integers, ranging from 0 to 255 inclusive

if any error, return (-1)
else return (0), success
*/
int	is_six_details_valid(t_scene *scene)
{
	if (is_end_with_xpm(scene->no) == -1 || \
		is_end_with_xpm(scene->so) == -1 || \
		is_end_with_xpm(scene->ea) == -1 || \
		is_end_with_xpm(scene->we) == -1)
	{
		ft_putstr_fd("Error\nWall texture file not .xpm extension\n", 2);
		return (-1);
	}	
	if (is_valid_rgb_array(scene->floor) == -1 || \
		is_valid_rgb_array(scene->ceiling) == -1)
	{
		ft_putstr_fd("Error\nProblematic RGB array value\n", 2);
		return (-1);
	}	
	return (0);
}

// ft_strcmp(&(s1[len - 4]), ".xpm")
int	is_end_with_xpm(char *s)
{
	int	len;

	len = ft_strlen(s);
	if ((s[len - 1] == 'm') && \
		(s[len - 2] == 'p') && \
		(s[len - 3] == 'x') && \
		(s[len - 4] == '.') \
		)
		return (0);
	else
		return (-1);
}
