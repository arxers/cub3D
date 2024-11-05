/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_char_valid_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:55:44 by jsu               #+#    #+#             */
/*   Updated: 2024/11/05 19:44:44 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/validate_input_bonus.h"

/*
NOTE. There are TWO versions of this function:
valid map chars
" \n10NSEW" (mandatory)
" \n10NSEWCDPX" (bonus)

checks tmp_map_buf in scene struct, char by char
if ft_strchr() returns NULL, means it is an invalid char,
	ie. a char NOT found in (char *)ref literal
	then return -1 (error)
else
	return 0 (success)
	
BONUS add 4 chars:
C: Collectible
D: Door
P: Powerloader
X: Xeno
*/
int	is_map_char_valid(char *s)
{
	const char	ref[] = " \n10NSEWCDPX";
	int			i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(ref, s[i]) == NULL)
		{
			ft_putstr_fd("Error\nInvalid map char\n", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	process_map(t_scene *scene)
{
	char	**tmp;

	if (trim_tmp_map_buf(&scene) == -1)
		return (-1);
	replace_space_with_zero(scene->tmp_map_buf);
	if (is_tmp_map_buf_split_by_empty_line(scene->tmp_map_buf) == -1)
		return (-1);
	tmp = ft_split(scene->tmp_map_buf, '\n');
	if (!tmp)
	{
		ft_putstr_fd("Error\nProblem with ft_split tmp_map_buf\n", 2);
		return (-1);
	}
	if (init_map_array(&scene->map, tmp, scene) == -1 || \
		init_map_array(&scene->map_bak, tmp, scene) == -1)
	{
		ft_putstr_fd("Error\nmalloc for map, fail\n", 2);
		return (-1);
	}
	load_map_data(tmp, scene);
	load_map_bak_data(tmp, scene);
	free_char_map(tmp);
	return (0);
}

/*
trim away:
leading AND trailing \n in tmp_map_buf
re-assign to scene->tmp_map_buf
*/
int	trim_tmp_map_buf(t_scene **scene)
{
	char	*tmp;
	char	*res;

	tmp = (*scene)->tmp_map_buf;
	res = ft_strtrim(tmp, "\n");
	if (!res)
	{
		ft_putstr_fd("Error\nProblem while preparing map\n", 2);
		return (-1);
	}
	(*scene)->tmp_map_buf = res;
	free(tmp);
	return (0);
}

/*
accepts a str (tmp_map_buf)
replaces space char, with 1 char, using ft_memset()

NOW, even when there is/are space char(s) in between map lines,
they will show up as 0/zeroes
so the next check, is_tmp_map_buf_split_by_empty_line(), will work
*/
void	replace_space_with_zero(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ')
			ft_memset((void *)&(s[i]), '0', sizeof(char));
		i++;
	}
}

/*
checks if 'big', trimmed tmp_map_buf (char *s), contains 'little ("\n\n")
if ft_strnstr returns non-NULL, means 'little' is found in 'big'
then return -1 (error)
*/
int	is_tmp_map_buf_split_by_empty_line(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (ft_strnstr(s, "\n\n", len) != NULL)
	{
		ft_putstr_fd("Error\nEmpty line found in between map lines\n", 2);
		return (-1);
	}
	return (0);
}
