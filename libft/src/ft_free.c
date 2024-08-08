/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:25:20 by jaslim            #+#    #+#             */
/*   Updated: 2024/08/03 23:44:29 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_free_void(void **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

void	*ft_free(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	return (NULL);
}

void	*ft_free_2d(char ***s)
{
	int	i;

	if (*s)
	{
		i = 0;
		while ((*s)[i])
		{
			free((*s)[i]);
			(*s)[i] = NULL;
			i++;
		}
		free(*s);
		*s = NULL;
	}
	return (NULL);
}

void	*ft_free_3d(char ****s)
{
	int	i;
	int	j;

	if (*s)
	{
		i = 0;
		while ((*s)[i])
		{
			j = 0;
			while ((*s)[i][j])
			{
				free((*s)[i][j]);
				(*s)[i][j] = NULL;
				j++;
			}
			free((*s)[i]);
			(*s)[i] = NULL;
			i++;
		}
		free(*s);
		*s = NULL;
	}
	return (NULL);
}
