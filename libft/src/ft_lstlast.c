/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:17:07 by jaslim            #+#    #+#             */
/*   Updated: 2023/09/26 20:22:27 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*
#include <stdio.h>

int	main()
{
	t_list *head;
	t_list *torso;
	t_list *legs;
	torso = malloc(sizeof(t_list));
	legs = malloc(sizeof(t_list));
	char	*neck = "throat";
	char	*knee = "caps";
	head = ft_lstnew("brain");
	torso->content = neck;
	legs->content = knee;
	ft_lstadd_back(&head, torso);
	ft_lstadd_back(&head, legs);
	while (head)
	{
		printf("%s\n", (char *)head->content);
		head = head->next;
	}
	printf("%s\n", (char *)ft_lstlast(head)->content);
	printf("%s\n", (char *)torso->content);
	printf("%s\n", (char *)legs->content);
}*/
