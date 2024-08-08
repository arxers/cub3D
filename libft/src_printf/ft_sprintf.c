/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:12:03 by jaslim            #+#    #+#             */
/*   Updated: 2024/06/11 21:28:56 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_sprintf_char(char *str, int c, int *count)
{
	if (str != NULL)
		str[*count] = c;
	(*count)++;
}

static void	ft_sprintf_str(char *str, char *format, int *count)
{
	int	i;
	int	len;

	len = ft_strlen(format);
	i = 0;
	while (i < len)
	{
		if (str != NULL)
			str[*count] = format[i];
		i++;
		(*count)++;
	}
}

static void	ft_sprintf_nbr(char *str, long long nbr, int *count)
{
	int		i;
	int		len;
	char	*nbr_str;

	nbr_str = ft_itoa(nbr);
	len = ft_strlen(nbr_str);
	i = 0;
	while (i < len)
	{
		if (str != NULL)
			str[*count] = nbr_str[i];
		i++;
		(*count)++;
	}
	free(nbr_str);
}

static void	ft_checkcase_sprintf(va_list a, char *str, char c, int *count)
{
	if (c == 'c')
		ft_sprintf_char(str, va_arg(a, int), count);
	else if (c == 's')
		ft_sprintf_str(str, va_arg(a, char *), count);
	else if (c == 'd')
		ft_sprintf_nbr(str, va_arg(a, long long), count);
	else if (c == '%')
		ft_sprintf_char(str, '%', count);
}

int	ft_sprintf(char *str, const char *format, ...)
{
	va_list	a;
	int		count;

	va_start(a, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format)
				ft_checkcase_sprintf(a, str, *format, &count);
		}
		else
			ft_sprintf_char(str, *format, &count);
		format++;
	}
	va_end(a);
	if (str != NULL)
		str[count] = '\0';
	return (count);
}
// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	char	str1[] = {"hello"};
// 	char	str2[] = {"world"};
// 	char	*str3 = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
// 	ft_sprintf(str3, "%s%s", str1, str2);
// 	printf("%s\n", str3);
// 	free(str3);
// }