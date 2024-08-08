/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 23:07:29 by jaslim            #+#    #+#             */
/*   Updated: 2024/06/01 02:32:00 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
/*
#include <stdio.h>

int	main(void)
{
	char	input[99];
	int		i;

	printf("input: ");
	scanf("%99s", input);
	while (input[i])
	{
		input[i] = ft_tolower(input[i]);
		i++;
	}
	printf("%s", input);
	return (0);
}*/
