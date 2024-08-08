/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 00:43:36 by jaslim            #+#    #+#             */
/*   Updated: 2023/09/16 19:00:36 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*byte_dest;
	const unsigned char	*byte_src;
	size_t				i;

	byte_dest = (unsigned char *)dest;
	byte_src = (const unsigned char *)src;
	i = n + 1;
	if (!byte_dest && !byte_src)
		return (dest);
	if (byte_src < byte_dest)
	{
		while (--i > 0)
			byte_dest[i - 1] = byte_src[i - 1];
	}
	else
	{
		i = -1;
		while (++i < n)
			byte_dest[i] = byte_src[i];
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str_ftmemmove[] = "abcde";
	char	str_memmove[] = "abcde";

	printf("before: %s\n", str_ftmemmove);
	ft_memmove(str_ftmemmove + 2, str_ftmemmove, 3);
	printf("after ft_memcpy: %s\n", str_ftmemmove);
	memmove(str_memmove + 2, str_memmove, 3);
	printf("after memcpy: %s\n", str_memmove);
}*/
