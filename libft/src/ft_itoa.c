/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:37:57 by jaslim            #+#    #+#             */
/*   Updated: 2023/09/22 19:30:06 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

static int	ft_intlen(int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ft_itostr(char *res, int n, int sign, int len)
{
	res[len + sign] = '\0';
	if (sign)
	{
		res[0] = '-';
		n = -n;
	}
	len += sign - 1;
	while (n > 0)
	{
		res[len] = (n % 10) + '0';
		len--;
		n = n / 10;
	}
}

char	*ft_itoa(int n)
{
	int		sign;
	int		len;
	char	*res;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = 0;
	if (n < 0)
		sign = 1;
	len = ft_intlen(n);
	res = malloc(len + 1 + sign);
	if (!res)
		return (NULL);
	ft_itostr(res, n, sign, len);
	return (res);
}
/*
#include <stdio.h>
int main ()
{
	printf("%s", ft_itoa(123));
}*/
