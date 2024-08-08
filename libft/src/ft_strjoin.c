/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:34:59 by jaslim            #+#    #+#             */
/*   Updated: 2024/08/04 12:42:26 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*safe_strjoin(char *s1, const char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (result == NULL)
		return (NULL);
	free(s1);
	return (result);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*s1_buffer;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	s1_buffer = malloc(len);
	if (!s1_buffer)
		return (NULL);
	ft_memcpy(s1_buffer, s1, ft_strlen(s1) + 1);
	ft_strlcat(s1_buffer, s2, len);
	return (s1_buffer);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_strjoin("seggs", "fault"));
}*/
