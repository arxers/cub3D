/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_rgb_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:41:04 by jsu               #+#    #+#             */
/*   Updated: 2024/11/04 13:41:07 by jsu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/validate_input.h"

/*
ft_split() the line, that starts with the expected identifier 'F'/'C'

CHECK #1. count the number of comma chars in the line

CHECK #2. ft_split() result, should only have 3 rows

CHECK #3. for each element in ft_split() result:
convert char array to int
check if int is between 0 to 255 inclusive
*/
int	is_valid_rgb_array(char *s)
{
	char	**arr;

	if (ft_count_char(s, ',') != 2)
		return (-1);
	arr = ft_split(s, ',');
	if (!arr)
		return (-1);
	if (ft_count_strings(arr) != 3
		|| is_valid_rgb_value(arr[0]) == -1
		|| is_valid_rgb_value(arr[1]) == -1
		|| is_valid_rgb_value(arr[2]) == -1)
	{
		free_char_map(arr);
		return (-1);
	}
	free_char_map(arr);
	return (0);
}

int	ft_count_char(char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count);
}

/*
accepts a (char *) argument
(char *) argument has to have minimum 1 char, or maximum 3 chars

each char in char array, must be a digit!

convert (char *) to integer
if (i is >= 0 && i <= 255)
	return 0 (success)
else
	return -1 (error)
*/
int	is_valid_rgb_value(char *s)
{
	int	i;
	int	len;

	len = ft_strlen(s);
	if (len == 0 || len > 3)
		return (-1);
	i = 0;
	while (i < len)
	{
		if (ft_isdigit(s[i]) == 0)
			return (-1);
		i++;
	}
	i = ft_atoi(s);
	if (i >= 0 && i <= 255)
		return (0);
	return (-1);
}

/*
converts an assumed VALID (char *) rgb array, eg. "0,42,255",
to an unsigned int, and returns this value
returns -1 (error)
*/
int	convert_rgb_array_to_int(char *s)
{
	int				r;
	int				g;
	int				b;
	char			**arr;

	arr = ft_split(s, ',');
	if (!arr)
		return (-1);
	r = ft_atoi(arr[0]);
	g = ft_atoi(arr[1]);
	b = ft_atoi(arr[2]);
	free_char_map(arr);
	return ((r << 16) | (g << 8) | b);
}
