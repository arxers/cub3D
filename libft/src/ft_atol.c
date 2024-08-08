/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:24:52 by jaslim            #+#    #+#             */
/*   Updated: 2024/02/27 18:19:17 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

long	ft_atol(const char *nptr)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (nptr[i])
	{
		while ((nptr[i] == ' ') || (nptr[i] >= 9 && nptr[i] <= 13))
			i++;
		if ((nptr[i] == '-') || (nptr[i] == '+'))
		{
			if (nptr[i] == '-')
				sign *= -1;
			i++;
		}
		while (ft_isdigit(nptr[i]))
		{
			result = result * 10 + (nptr[i] - '0');
			i++;
		}
	}
	return (result *= sign);
}
/*
#include <stdio.h>

int	main(int ac, char **av)
{
	if (ac == 2)
		printf("%d", ft_atoi(av[1]));
}*/
