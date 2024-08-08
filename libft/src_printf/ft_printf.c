/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:12:03 by jaslim            #+#    #+#             */
/*   Updated: 2024/07/07 00:00:53 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_checkcase(int fd, va_list a, char c, int *count)
{
	if (c == 'c')
		ft_putchar(fd, va_arg(a, int), count);
	else if (c == 's')
		ft_putstr(fd, va_arg(a, char *), count);
	else if (c == 'p')
		ft_putptr(fd, va_arg(a, void *), count);
	else if (c == 'd')
		ft_putnbr(fd, va_arg(a, int), count);
	else if (c == 'i')
		ft_putnbr(fd, va_arg(a, int), count);
	else if (c == 'u')
		ft_putunbr(fd, va_arg(a, unsigned int), count);
	else if (c == 'x')
		ft_puthex(fd, va_arg(a, unsigned int), "0123456789abcdef", count);
	else if (c == 'X')
		ft_puthex(fd, va_arg(a, unsigned int), "0123456789ABCDEF", count);
	else if (c == '%')
		ft_putchar(fd, '%', count);
	else
	{
		ft_putchar(fd, '%', count);
		ft_putchar(fd, c, count);
	}
}

static int	ft_isspace_printf(int c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	a;
	int		count;

	va_start(a, s);
	count = 0;
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			while (ft_isspace_printf(*s))
				s++;
			if (*s)
				ft_checkcase(1, a, *s, &count);
			else
				return (-1);
		}
		else
			ft_putchar(1, *s, &count);
		s++;
	}
	va_end(a);
	return (count);
}
/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*nilpointer;
	nilpointer = malloc(9999999999999999);
	char	mychar = 'A';
	char	nullchar = '\0';
	char	string[] = "pukimak";
	char	estring[] = "";
	int	i = 54321;
	unsigned int	u = 12345;
	unsigned long long x = 1112345678999;
	unsigned long long x0 = 0;
	ft_printf("%%c: %c\n", mychar);
	ft_printf("\\0 %%c: %c\n", nullchar);
	ft_printf("%%s: %s\n", string);
	ft_printf("empty %%s: %s\n", estring);
	ft_printf("%p\n", nilpointer);
	ft_printf("%%d: %d\n", i);
	ft_printf("%%u: %u\n", u);
	ft_printf("%%x: %x\n", x);	
	ft_printf("%%x = 0: ", x0);	
}*/
