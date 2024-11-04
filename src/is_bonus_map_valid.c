/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_bonus_map_valid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:12:23 by jsu               #+#    #+#             */
/*   Updated: 2024/11/04 19:27:04 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/validate_input.h"

// int	is_bonus_map_valid(t_scene *scene)
// {
// 	if (is_num_player_valid(scene->map) == -1
// 		|| load_player_pos(scene->map, scene) == -1
// 		|| is_num_xeno_valid(scene->map) == -1
// 		|| load_xeno_pos(scene->map, scene) == -1
// 		|| is_num_powerloader_valid(scene->map) == -1
// 		|| load_powerloader_pos(scene->map, scene) == -1
// 		|| is_num_collectibles_valid(scene->map) == -1)
// 		return (-1);
// 	ff_bonus(scene->p_pos.y, scene->p_pos.x, scene);
// 	if (is_fill_char_at_map_border(scene) == 0)
// 		return (-1);
// 	return (0);
// }

/*
wrapper for count_char_in_map()

scan the map, and count the number of valid player chars
if sum total of valid player char is NOT one, return -1 (error)
else return 0 (success) 
*/
int	is_num_player_valid(char **map)
{
	int	num_n;
	int	num_s;
	int	num_e;
	int	num_w;

	num_n = count_char_in_map(map, 'N');
	num_s = count_char_in_map(map, 'S');
	num_e = count_char_in_map(map, 'E');
	num_w = count_char_in_map(map, 'W');
	if (num_n + num_s + num_e + num_w != 1)
	{
		ft_putstr_fd("Error\nIncorrect number of PLAYER char in map\n", 2);
		return (-1);
	}
	return (0);
}

/*
returns the count of chars 'ch' found in (char **)map
*/
int	count_char_in_map(char **map, char ch)
{
	int	i;
	int	j;
	int	res;

	res = 0;
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == ch)
				res += 1;
			j++;
		}
		i++;
	}
	return (res);
}

/*
returns 0 (success) after finding the first occurrence of a valid PLAYER char,
'N'/'S'/'E'/'W'
SIDE EFFECT: load its coordinates into (t_point) scene->pos_player
*/
int	load_player_pos(char **map, t_scene *scene)
{
	int		i;
	int		j;
	char	*player;

	player = "NSEW";
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (ft_strchr(player, map[i][j]))
			{
				scene->p_pos.x = j;
				scene->p_pos.y = i;
				return (0);
			}
			j++;
		}
		i++;
	}
	ft_putstr_fd("Error\nPLAYER char missing from map\n", 2);
	return (-1);
}

/*
same as mandatory version
only difference is first arg for ft_strchr() includes 4 extra chars: C D X P
*/
void	ff_bonus(int i, int j, t_scene *s)
{
	if (i < 0 || i > s->map_dim.y - 1)
		return ;
	if (j < 0 || j > s->map_dim.x - 1)
		return ;
	if (s->map_bak[i][j] == '1' || s->map_bak[i][j] == 'F')
		return ;
	if (s->map_bak[i][j] == '0' || ft_strchr("NSEWCDXP", s->map_bak[i][j]))
		s->map_bak[i][j] = 'F';
	ff_bonus(i - 1, j, s);
	ff_bonus(i + 1, j, s);
	ff_bonus(i, j - 1, s);
	ff_bonus(i, j + 1, s);
}
