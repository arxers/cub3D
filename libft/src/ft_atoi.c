/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jerlim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:24:52 by jaslim            #+#    #+#             */
/*   Updated: 2024/05/08 21:29:42 by jerlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	if (nptr && nptr[i])
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
