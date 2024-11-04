/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_fill_char_at_map_border.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:24:58 by jsu               #+#    #+#             */
/*   Updated: 2024/11/04 14:25:00 by jsu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/validate_input.h"

/*
If a fill char is found in any border side of the map,
then return 0 (success) 

NOTE. If there is a fill char at the map's border. REJECT the map
*/
int	is_fill_char_at_map_border(t_scene *s)
{
	if ((is_fill_char_at_toprow(s) == 0) || \
		(is_fill_char_at_botrow(s) == 0) || \
		(is_fill_char_at_lcol(s) == 0) || \
		(is_fill_char_at_rcol(s) == 0))
	{
		ft_putstr_fd("Error\nFlood fill char found at border wall\n", 2);
		return (0);
	}
	return (-1);
}

/*
set a tmp (char *) ptr to the TOP row of map
iterate thru chars in the row,
if fill char 'F' found, return 0 (success)
else return -1 (failure)
*/
int	is_fill_char_at_toprow(t_scene *s)
{
	int		i;

	i = 0;
	while (s->map_bak[0][i] != '\0')
	{
		if (s->map_bak[0][i] == 'F')
			return (0);
		i++;
	}
	return (-1);
}

/*
set a tmp (char *) ptr to the BOTTOM row of map
iterate thru chars in the row,
if fill char 'F' found, return 0 (success)
else return -1 (failure)
*/
int	is_fill_char_at_botrow(t_scene *s)
{
	int		i;

	i = 0;
	while (s->map_bak[s->map_dim.y - 1][i] != '\0')
	{
		if (s->map_bak[s->map_dim.y - 1][i] == 'F')
			return (0);
		i++;
	}
	return (-1);
}

/*
iterate thru rows in the map
if fill char 'F' found in LEFT col, return 0 (success)
else return -1 (failure)
*/
int	is_fill_char_at_lcol(t_scene *s)
{
	int	i;

	i = 0;
	while (s->map_bak[i] != NULL)
	{
		if (s->map_bak[i][0] == 'F')
			return (0);
		i++;
	}
	return (-1);
}

/*
iterate thru rows in the map
if fill char 'F' found in RIGHT col, return 0 (success)
else return -1 (failure)
*/
int	is_fill_char_at_rcol(t_scene *s)
{
	int	i;

	i = 0;
	while (s->map_bak[i] != NULL)
	{
		if (s->map_bak[i][s->map_dim.x - 1] == 'F')
			return (0);
		i++;
	}
	return (-1);
}
