/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 00:21:18 by jaslim            #+#    #+#             */
/*   Updated: 2024/06/27 01:34:17 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_print_fd(int fd)
{
	char	*s;

	ft_printf("Don't forget that this advances the fd!!\n");
	ft_printf("\033[1;34m--- print_fd(%d) START ---\033[0m\n", fd);
	s = get_next_line(fd);
	while (s != NULL)
	{
		ft_printf("%s", s);
		free(s);
		s = get_next_line(fd);
	}
	ft_printf("\033[1;34m--- print_fd(%d) END ---\033[0m\n", fd);
}
