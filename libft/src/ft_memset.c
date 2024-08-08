/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:24:05 by jaslim            #+#    #+#             */
/*   Updated: 2023/09/17 14:59:08 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*byte_s;
	size_t			i;

	i = -1;
	byte_s = (unsigned char *)s;
	while (++i < n)
		byte_s[i] = (unsigned char)c;
	return (s);
}
/*
#include <stdio.h>

int	main()
{
	char test[] = "poop";
	ft_memset(test, 'c', 1);
	ft_memset(test + 2, 'c', 1);
	ft_memset(test + 3, 'k', 1);
}*/
