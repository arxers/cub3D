/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 07:30:43 by jaslim            #+#    #+#             */
/*   Updated: 2024/07/09 07:43:46 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_count_strings(char **array)
{
	int	count;

	count = 0;
	while (*array != NULL)
	{
		count++;
		array++;
	}
	return (count);
}
