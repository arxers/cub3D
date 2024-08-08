/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 22:39:48 by jaslim            #+#    #+#             */
/*   Updated: 2024/06/01 02:32:35 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
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
	if (ft_isalnum(input))
		printf("%c is alphanumeric.\n", input);
	else
		printf("%c is not alphanumeric.\n", input);
	return (0);
}*/
