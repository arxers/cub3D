/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_alnum.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 20:07:22 by jaslim            #+#    #+#             */
/*   Updated: 2024/07/07 00:00:46 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putchar(int fd, int c, int *count)
{
	*count += write (fd, &c, 1);
}

void	ft_putstr(int fd, char *s, int *count)
{
	int	i;

	if (!s)
	{
		*count += write(fd, "(null)", 6);
		return ;
	}
	i = 0;
	while (s[i])
		i++;
	*count += write(fd, s, i);
}

void	ft_putnbr(int fd, long long n, int *count)
{
	if (n < 0)
	{
		ft_putchar(fd, '-', count);
		n = -n;
	}
	if (n <= 9)
		ft_putchar(fd, n + '0', count);
	else
	{
		ft_putnbr(fd, n / 10, count);
		ft_putnbr(fd, n % 10, count);
	}
}

void	ft_putunbr(int fd, unsigned long long n, int *count)
{
	if (n <= 9)
		ft_putchar(fd, n + '0', count);
	else
	{
		ft_putunbr(fd, n / 10, count);
		ft_putunbr(fd, n % 10, count);
	}
}
