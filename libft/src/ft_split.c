/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:04:49 by jaslim            #+#    #+#             */
/*   Updated: 2024/06/04 17:45:12 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	*ft_free_split(char **split_str, size_t i)
{
	while (i > 0)
		free(split_str[--i]);
	free(split_str);
	return (NULL);
}

static size_t	ft_wordcount(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (s && *s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	**ft_ft_split(char **res, char const *s, char c, size_t count)
{
	size_t		i;
	char const	*start;

	i = 0;
	while (*s && i < count)
	{
		while (*s && *s == c)
			s++;
		start = s;
		while (*s && *s != c)
			s++;
		res[i] = ft_substr(start, 0, s - start);
		if (!res[i])
		{
			ft_free_split(res, i);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	count;

	count = ft_wordcount(s, c);
	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	res = ft_ft_split(res, s, c, count);
	return (res);
}

// char	**ft_split(char const *s, char c)
// {
// 	size_t		i;
// 	char const	*start;
// 	char		**split_str;
// 	char const	*str;

// 	i = 0;
// 	str = s;
// 	split_str = malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
// 	if (!split_str)
// 		return (NULL);
// 	while (*s && i < ft_wordcount(str, c))
// 	{
// 		while (*s && *s == c)
// 			s++;
// 		start = s;
// 		while (*s && *s != c)
// 			s++;
// 		split_str[i] = ft_substr(start, 0, s - start);
// 		if (!split_str[i])
// 			return (ft_free_split(split_str, i));
// 		i++;
// 	}
// 	split_str[i] = NULL;
// 	return (split_str);
// }
/*
#include <stdio.h>

int	main(void)
{
	int	i = 0;
	char	**res = ft_split("   ", ' ');
	while (res[i])
	{
		printf("%s\n", res[i]);
		i++;
	}
//	printf("%zu", ft_wordcount(" str1 str2 str3  aa a ", ' '));
//	
//	
	//printf("%s", ft_split(" aaaa a  aa  aa a ", ' ')[1]);
	//printf("%s", ft_split(" aaaa a  aa  aa a ", ' ')[2]);
}*/
