/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_chars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:17:55 by jsu               #+#    #+#             */
/*   Updated: 2024/11/05 19:29:02 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/validate_input.h"

int	is_num_xeno_valid(char **map)
{
	int	num_enemy;

	num_enemy = count_char_in_map(map, 'X');
	if (num_enemy != 1)
	{
		ft_putstr_fd("Error\nIncorrect number of ENEMY char in map\n", 2);
		return (-1);
	}
	return (0);
}

/*
returns 0 (success) after finding the first occurrence of a valid ENEMY char, 'X'
SIDE EFFECT: load coordinates into (t_point) scene->pos_xeno
*/
int	load_xeno_pos(char **map, t_scene *scene)
{
	int		i;
	int		j;
	char	*enemy;

	enemy = "X";
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (ft_strchr(enemy, map[i][j]))
			{
				scene->pos_xeno.x = j;
				scene->pos_xeno.y = i;
				return (0);
			}
			j++;
		}
		i++;
	}
	ft_putstr_fd("Error\nENEMY char missing from map\n", 2);
	return (-1);
}

int	is_num_powerloader_valid(char **map)
{
	int	num_armor;

	num_armor = count_char_in_map(map, 'P');
	if (num_armor != 1)
	{
		ft_putstr_fd("Error\nIncorrect number of ARMOR char in map\n", 2);
		return (-1);
	}
	return (0);
}

/*
returns 0 (success) after finding the first occurrence of a valid ENEMY char, 'X'
SIDE EFFECT: load coordinates into (t_point) scene->pos_xeno
*/
int	load_powerloader_pos(char **map, t_scene *scene)
{
	int		i;
	int		j;
	char	*armor;

	armor = "P";
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (ft_strchr(armor, map[i][j]))
			{
				scene->pos_powerloader.x = j;
				scene->pos_powerloader.y = i;
				return (0);
			}
			j++;
		}
		i++;
	}
	ft_putstr_fd("Error\nARMOR char missing from map\n", 2);
	return (-1);
}

int	is_num_collectibles_valid(char **map)
{
	int	num_collectible;

	num_collectible = count_char_in_map(map, 'C');
	if (num_collectible < REQUIRED_ITEMS)
	{
		ft_putstr_fd("Error\nIncorrect number of COLLECTIBLE char in map, ", 2);
		ft_putstr_fd("expected ", 2);
		ft_putnbr_fd(REQUIRED_ITEMS, 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	return (0);
}
