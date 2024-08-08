/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:23:26 by jaslim            #+#    #+#             */
/*   Updated: 2024/01/09 18:03:30 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// malloc the BUFFER_SIZE + 1 for the null terminator
// stores BUFFER_SIZE of bytes into buf_right
// error handling for read errors
// null terminates buf_right
// duplicates the mem into the buf_left then frees mem
// combines buf_left and buf_right, assigns it to mem, and frees buf_left
// checks for '\n' and if its true, breaks the loop, frees buf_right and returns
int	read_and_append(char **mem, char **buf_left, int fd)
{
	int		bytes;
	char	*buf_right;

	bytes = 1;
	buf_right = malloc(BUFFER_SIZE + 1);
	if (!buf_right)
		return (0);
	while (bytes > 0)
	{
		bytes = read(fd, buf_right, BUFFER_SIZE);
		if (bytes == -1)
		{
			ft_free_gnl(&buf_right, mem, NULL);
			return (0);
		}
		buf_right[bytes] = '\0';
		*buf_left = ft_strdup_gnl(*mem);
		ft_free_gnl(mem, NULL, NULL);
		*mem = ft_strjoin_gnl(*buf_left, buf_right);
		ft_free_gnl(buf_left, NULL, NULL);
		if (check_nl(*mem))
			break ;
	}
	ft_free_gnl(&buf_right, NULL, NULL);
	return (0);
}

// searches for where the '\n' appears, and the total len of the array
// to calculate how much to malloc
// copies from 1 byte after the '\n', until the end of the array
// free mem before returning the leftovers
char	*assign_leftovers(char **mem)
{
	char	*assign_leftovers;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (mem[0][i] && mem[0][i] != '\n')
		i++;
	if (mem[0][i] == '\n')
		i++;
	while (mem[0][j])
		j++;
	assign_leftovers = malloc(j - i + 1);
	if (!assign_leftovers)
		return (NULL);
	j = 0;
	while (mem[0][i + j])
	{
		assign_leftovers[j] = mem[0][i + j];
		j++;
	}
	assign_leftovers[j] = '\0';
	ft_free_gnl(mem, NULL, NULL);
	return (assign_leftovers);
}

// iterate mem[i] until it finds the newline, uses i to malloc
// then copies it to res (includes the '\n')
char	*assign_line(char *mem)
{
	int		i;
	char	*res;

	i = 0;
	while (mem[i] && mem[i] != '\n')
		i++;
	if (mem[i] == '\n')
		i++;
	res = malloc(i + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (mem[++i] && mem[i] != '\n')
		res[i] = mem[i];
	if (mem[i] == '\n')
	{
		res[i] = mem[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*mem = NULL;
	char		*buf_left;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		ft_free_gnl(&mem, NULL, NULL);
		return (NULL);
	}
	res = NULL;
	buf_left = NULL;
	read_and_append(&mem, &buf_left, fd);
	if (!mem)
		return (NULL);
	if (!*mem)
		ft_free_gnl(&mem, NULL, NULL);
	if (mem && *mem)
	{
		res = assign_line(mem);
		mem = assign_leftovers(&mem);
	}
	if (!res)
		ft_free_gnl(&mem, NULL, NULL);
	return (res);
}
/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd = open("fd.txt", O_RDONLY);
	char *str;
	int i;

	i = 0;
	while (i < 12)
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
		i++;
	}
}*/
