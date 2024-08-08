/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 22:32:21 by jaslim            #+#    #+#             */
/*   Updated: 2024/06/01 02:32:18 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
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
	if (ft_isdigit(input))
		printf("%c is a digit.\n", input);
	else
		printf("%c is not a digit.\n", input);
	return (0);
}*/
