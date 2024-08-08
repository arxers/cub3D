/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 22:24:04 by jaslim            #+#    #+#             */
/*   Updated: 2024/06/01 02:31:54 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
/*
#include <stdio.h>

int	main(void)
{
	char	input[99];
	int		i;

	i = 0;
	printf("input: ");
	scanf("%99s", input);
	while (input[i])
	{
		input[i] = ft_toupper(input[i]);
		i++;
	}
	printf("%s\n", input);
	return (0);
}*/
