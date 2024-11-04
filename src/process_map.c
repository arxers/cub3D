/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:02:56 by jsu               #+#    #+#             */
/*   Updated: 2024/11/04 14:02:59 by jsu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/validate_input.h"

/*
accepts a (char **)tmp_map, and ptr to scene struct
callocs space for (char **) for scene->map
*/
int	init_map_array(char ***map, char **map_temp, t_scene *scene)
{
	t_vec	index;

	count_map_area(map_temp, scene);
	*map = ft_calloc(scene->map_dim.y + 1, sizeof(char *));
	if (!*map)
		return (-1);
	index.y = 0;
	while (index.y < scene->map_dim.y)
	{
		(*map)[index.y] = ft_calloc (scene->map_dim.x + 1, sizeof(char));
		if (!(*map)[index.y])
			return (-1);
		ft_memset((*map)[index.y], '0', scene->map_dim.x);
		index.y++;
	}
	return (0);
}

/*
calculates the map's dimensions
and assign the values to map_width & map_height, in 'scene' struct
*/
void	count_map_area(char **map_temp, t_scene *scene)
{
	t_vec	index;
	int		count;
	int		max_x;

	count = 0;
	max_x = 0;
	index.y = 0;
	while (map_temp[index.y])
	{
		index.x = 0;
		count = 0;
		while (map_temp[index.y][index.x])
		{
			count++;
			index.x++;
		}
		if (count > max_x)
			max_x = count;
		index.y++;
	}
	scene->map_dim.x = max_x;
	scene->map_dim.y = index.y;
}

/*
copy data from src, (char **)tmp map
to scene->map
*/
void	load_map_data(char **s, t_scene *scene)
{
	char	**dst;
	int		i;
	int		j;
	int		len;

	dst = scene->map;
	i = 0;
	while (s[i] != NULL)
	{
		j = 0;
		len = ft_strlen(s[i]);
		while (j < len)
		{
			dst[i][j] = s[i][j];
			j++;
		}
		i++;
	}
}

/*
copy data from src, (char **)tmp map
to dst: scene->map_bak
*/
void	load_map_bak_data(char **s, t_scene *scene)
{
	char	**dst;
	int		i;
	int		j;
	int		len;

	dst = scene->map_bak;
	i = 0;
	while (s[i] != NULL)
	{
		j = 0;
		len = ft_strlen(s[i]);
		while (j < len)
		{
			dst[i][j] = s[i][j];
			j++;
		}	
		i++;
	}
}
