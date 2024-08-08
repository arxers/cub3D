/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:10:23 by jaslim            #+#    #+#             */
/*   Updated: 2023/09/27 20:55:08 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*temp;

	new_list = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		temp = f(lst->content);
		new_node = ft_lstnew(temp);
		if (!new_node)
		{
			if (temp)
				del(temp);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
/*
memory leak = (!node), (*del), lstclear, free
iterates = lst = lst->next 
creates a new list = lstnew, lstadd_front

ft_lstclear(t_list **lst, void(*del)(void*));
ft_lstnew(void *content);
ft_lstadd_front(t_list **lst, t_list *new);

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	void	*node;
	void	*tmp;

	if (!lst || !f || !del)
		return (NULL);
	tmp = f(lst->content);
	new = ft_lstnew(f(lst->content));
	while (lst)
	{
		ft_lstadd_front(*new, node);

	if (!new)
	{
		if (!tmp)
			del(tmp);
		ft_lstclear(*new, del);
		*new = NULL;
		return (new);
	}
*/
