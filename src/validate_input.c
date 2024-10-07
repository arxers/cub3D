#include "../inc/cub3D.h"

// when success, return 0
// when failure return 1

// check num of cmdline args
void check_n_cmdline_args(int ac)
{
	if (ac != 2)
	{
		ft_putstr_fd("cub3D: Invalid number of arguments\n", 2);
		ft_putstr_fd("cub3D: usage: cub3D [*.cub]\n", 2);
		exit(1);
	}
}

// check if map ends with ".cub"
void	is_map_a_dot_cub_file(char *s)
{
	int	len;
	
	len = ft_strlen(s);
	if ((s[len - 1] == 'b') && \
		(s[len - 2] == 'u') && \
		(s[len - 3] == 'c') && \
		(s[len - 4] == '.') \
		)
		return ;
	else
	{
		ft_putstr_fd("cub3D: Map does not end in .cub\n", 2);
		ft_putstr_fd("cub3D: usage: cub3D [*.cub]\n", 2);
		exit(1);
	}
}

// check if .cub extension
int	is_cub_ext(char *s)
{
	int	len;
	
	len = ft_strlen(s);
	if ((s[len - 1] == 'b') && \
		(s[len - 2] == 'u') && \
		(s[len - 3] == 'c') && \
		(s[len - 4] == '.') \
		)
	return (0);
	else
		return (1);
}	
