/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:02:23 by jaslim            #+#    #+#             */
/*   Updated: 2024/06/05 18:47:39 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtok_dup(char *str, const char *delim)
{
	static char	*last = NULL;
	char		*start;
	char		*token;

	if (str == NULL && last == NULL)
		return (NULL);
	if (str != NULL)
		last = str;
	while (*last && ft_strchr(delim, *last))
		last++;
	if (*last == '\0')
		return (NULL);
	start = last;
	while (*last && ft_strrchr(delim, *last) == NULL)
		last++;
	token = malloc((last - start) + 1);
	if (!token)
		return (NULL);
	ft_memcpy(token, start, (last - start) + 1);
	token[(last - start)] = '\0';
	return (token);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last = NULL;
	char		*start;

	if (str == NULL && last == NULL)
		return (NULL);
	if (str != NULL)
		last = str;
	while (*last && ft_strchr(delim, *last))
		last++;
	if (*last == '\0')
		return (NULL);
	start = last;
	while (*last && ft_strrchr(delim, *last) == NULL)
		last++;
	if (!*last)
		last = NULL;
	else
	{
		*last = '\0';
		last++;
	}
	return (start);
}

// #include <stdio.h>
// #include <string.h>

// int main(int ac, char **av)
// {
//     char    *token;

// 	if (ac == 3)
// 	{
// 		printf("original str:%s\n", av[1]);
// 		token = ft_strtok(av[1], av[2]);
// 		while (token != NULL)
// 		{
// 			printf("%s\n", token);
// 			token = ft_strtok(NULL, av[2]);
// 		}
// 		printf("original str:%s\n", av[1]);
// 	}
//     return (0);
// }

// int main(int ac, char **av)
// {
//     char    *token;

// 	if (ac == 3)
// 	{
// 		printf("original str:%s\n", av[1]);
// 		token = ft_strtok_dup(av[1], av[2]);
// 		while (token != NULL)
// 		{
// 			printf("%s\n", token);
// 			free(token);
// 			token = ft_strtok_dup(NULL, av[2]);
// 		}
// 		printf("original str:%s\n", av[1]);
// 		free(token);
// 	}
//     return (0);
// }