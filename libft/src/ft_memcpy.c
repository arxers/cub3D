/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 22:17:38 by jaslim            #+#    #+#             */
/*   Updated: 2023/09/16 18:44:02 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*byte_dest;
	const unsigned char	*byte_src;
	size_t				i;

	byte_dest = (unsigned char *)dest;
	byte_src = (const unsigned char *)src;
	i = -1;
	if (!byte_dest && !byte_src)
		return (dest);
	while (++i < n)
		byte_dest[i] = byte_src[i];
	return (byte_dest);
}
/*
#include <stdio.h>

int	main(void)
{
	char	src[] = "Hello, World";
	char	dest[99];

	ft_memcpy(dest, src, sizeof(src));
	printf("%s", dest);
	return (0);
}*/
