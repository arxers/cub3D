/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:06:27 by jaslim            #+#    #+#             */
/*   Updated: 2023/11/07 17:08:44 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

char	*ft_strdup_gnl(char *s)
{
	char	*dupe;
	int		i;

	if (s == NULL)
		return (ft_strdup_gnl(""));
	i = 0;
	while (s[i])
		i++;
	dupe = malloc(i + 1);
	if (!dupe)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dupe[i] = s[i];
		i++;
	}
	dupe[i] = '\0';
	return (dupe);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*joined;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	joined = malloc(i + j + 1);
	if (!joined)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		joined[i] = s1[i];
	while (s2[++j])
		joined[i + j] = s2[j];
	joined[i + j] = '\0';
	return (joined);
}

void	ft_free_gnl(char **c, char **u, char **m)
{
	if (c && *c)
	{
		free(*c);
		*c = NULL;
	}
	if (u && *u)
	{
		free(*u);
		*u = NULL;
	}
	if (m && *m)
	{
		free(*m);
		*m = NULL;
	}
}

int	check_nl(char *mem)
{
	int	i;

	i = 0;
	while (mem[i])
	{
		if (mem[i] == '\n')
		{
			i++;
			return (i);
		}
		i++;
	}
	return (0);
}
