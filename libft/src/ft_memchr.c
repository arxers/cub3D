/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:52:15 by jaslim            #+#    #+#             */
/*   Updated: 2023/09/15 22:54:23 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s_byte;
	size_t				i;

	s_byte = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (s_byte[i] == (unsigned char)c)
			return ((void *)s_byte + i);
		i++;
	}
	return (NULL);
}
