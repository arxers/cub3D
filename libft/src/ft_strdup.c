/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 19:58:12 by jaslim            #+#    #+#             */
/*   Updated: 2023/09/09 20:53:54 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	char	*dupe;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
		i++;
	dupe = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	if (!dupe)
		return (NULL);
	while (str[i])
	{
		dupe[i] = str[i];
		i++;
	}
	dupe[i] = '\0';
	return (dupe);
}
/*
#include <stdio.h>

int	main(int ac, char **av)
{
	char	*dupe;

	if (ac == 2)
	{
		dupe = ft_strdup(av[1]);
		if (dupe)
		{
			printf("%s\n", dupe);
			free(dupe);
		}
		else
			printf("lol");
	}
	return (0);
}*/
