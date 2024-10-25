/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_jason.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:01:10 by jaslim            #+#    #+#             */
/*   Updated: 2024/10/25 21:07:40 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

t_point	count_map_area(char **map_temp, t_scene *scene)
{
	t_point	index;
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
	return ((t_point){max_x, index.y});
}

int	init_map_array(char **map_temp, t_scene *scene)
{
	t_point	map_size;
	t_point	index;

	map_size = count_map_area(map_temp, scene);
	scene->map = ft_calloc(map_size.y + 1, sizeof(char *));
	if (!scene->map)
		return (-1);
	index.y = 0;
	while (index.y < map_size.y)
	{
		scene->map[index.y] = ft_calloc (map_size.x + 1, sizeof(char));
		if (!scene->map[index.y])
			return (-1);
		index.y++;
	}
	index.y = 0;
	while (scene->map[index.y])
	{
		index.x = 0;
		while (index.x < map_size.x)
		{
			scene->map[index.y][index.x] = '1';
			index.x++;
		}
		index.y++;
	}
	return (0);
}

int	main(void)
{
	int	i;

	t_scene	scene;
	char	**map = (char *[])
	{
		"111111111111111",
		"                 ",
		"111",
		NULL
	};
	init_map_array(map, &scene);
	for (int i = 0; scene.map[i]; i++)
		printf("%s\n", scene.map[i]);
}
