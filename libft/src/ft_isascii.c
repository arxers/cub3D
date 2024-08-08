/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:00:37 by jaslim            #+#    #+#             */
/*   Updated: 2024/06/01 02:32:10 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	int	i;
	char	test[] = {'A', 'B', 42, 128, 32, -1};

	i = 0;
	while (test[i] != 0)
	{
		if (ft_isascii(test[i]))
			printf("%c is ASCII.\n", test[i]);
		else
			printf("%c is not ASCII.\n", test[i]);
		i++;
	}
	return (0);
}*/
