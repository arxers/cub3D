/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:24:16 by jaslim            #+#    #+#             */
/*   Updated: 2024/07/07 00:01:46 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_puthex(int fd, unsigned long long n, char *base, int *count)
{
	if (n <= 15)
		ft_putchar(fd, base[n % 16], count);
	else
	{
		ft_puthex(fd, n / 16, base, count);
		ft_puthex(fd, n % 16, base, count);
	}
}

void	ft_putptr(int fd, void *n, int *count)
{
	if (!n)
		*count += write(fd, "(nil)", 5);
	else
	{
		ft_putstr(fd, "0x", count);
		ft_puthex(fd, (unsigned long long)n, "0123456789abcdef", count);
	}
}
/*
"0123456789"
"0123456789abcdef"
if base == 10
	if nbr > 9
		puthex(nbr /10 base count)
	base[nbr %10]
else if base == 16
	if nbr > 15
		puthex(nbr / 16 base count)
	base[nbr % 16]

void	ft_putptr(int *count)
{
	ft_putstr("0x", count);
	ft_putstr((unsigned long long) va_arg(a, void *);
}*/
