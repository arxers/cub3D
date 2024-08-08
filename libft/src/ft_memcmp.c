/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 22:54:55 by jaslim            #+#    #+#             */
/*   Updated: 2023/09/17 15:03:13 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_byte;
	const unsigned char	*s2_byte;
	size_t				i;

	i = 0;
	s1_byte = (const unsigned char *)s1;
	s2_byte = (const unsigned char *)s2;
	while (i < n)
	{
		if (s1_byte[i] != s2_byte[i])
			return (s1_byte[i] - s2_byte[i]);
		i++;
	}
	return (0);
}
