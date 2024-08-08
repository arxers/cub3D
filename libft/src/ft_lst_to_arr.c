/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:53:21 by jaslim            #+#    #+#             */
/*   Updated: 2024/05/16 18:53:51 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

char	**ft_lst_to_arr(t_list **lst)
{
	char	**arr;
	int		i;
	t_list	*current;

	arr = malloc(sizeof(char *) * (ft_lstsize(*lst) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	current = *lst;
	while (i < ft_lstsize(*lst))
	{
		arr[i] = ft_strdup((char *)current->content);
		if (!arr[i])
		{
			while (i > 0)
				free(arr[--i]);
			free(arr);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
