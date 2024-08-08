/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 21:57:49 by jaslim            #+#    #+#             */
/*   Updated: 2024/06/01 02:32:14 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	char	input;

	printf("input: ");
	scanf("%c", &input);
	if (ft_isalpha(input))
		printf("%c is alpha.\n", input);
	else
		printf("%c is not alpha. \n", input);
	return (0);
}*/
