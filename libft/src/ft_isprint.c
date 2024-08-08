/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 21:02:46 by jaslim            #+#    #+#             */
/*   Updated: 2024/06/01 02:32:22 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	int	i;
	char	test[] = {1, 20, 32, 61, 62, 63};

	i = 0;
	while (test[i] != 0)
	{
		if (ft_isprint(test[i]))
			printf("%c is printable.\n", test[i]);
		else
			printf("%c wapuriintabarujanaidesu.\n", test[i]);
		i++;
	}
	return (0);
}*/
