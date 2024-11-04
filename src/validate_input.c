/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:20:28 by jsu               #+#    #+#             */
/*   Updated: 2024/11/04 07:41:56 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/validate_input.h"

void	print_2d_map(char **s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] != NULL)
	{
		j = 0;
		while (s[i][j] != '\0')
		{
			write(1, &(s[i][j]), 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void	print_scene_struct(t_scene *scene)
{
	printf("\nCurrent state of t_scene struct:\n");
	printf("NO:%s\n", scene->no);
	printf("SO:%s\n", scene->so);
	printf("EA:%s\n", scene->ea);
	printf("WE:%s\n", scene->we);
	printf("F:%s\n", scene->floor);
	printf("hex_floor:%x\n", scene->hex_floor);
	printf("C:%s\n", scene->ceiling);
	printf("hex_ceiling:%x\n", scene->hex_ceiling);
	printf("tmp_map_buf (char *) begin on new line:\n%s\n", scene->tmp_map_buf);
	printf("map ptr (char **): %p\n", scene->map);
	print_2d_map(scene->map);
	printf("map_bak ptr (char **): %p\n", scene->map_bak);
	print_2d_map(scene->map_bak);
	printf("map_width: %d\n", scene->map_dim.x);
	printf("map_height: %d\n", scene->map_dim.y);
	printf("pos_player.x: %d\n", scene->p_pos.x);
	printf("pos_player.y: %d\n", scene->p_pos.y);
	printf("pos_xeno.x: %d\n", scene->pos_xeno.x);
	printf("pos_xeno.y: %d\n", scene->pos_xeno.y);
	printf("pos_powerloader.x: %d\n", scene->pos_powerloader.x);
	printf("pos_powerloader.y: %d\n", scene->pos_powerloader.y);
}

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	printf("print_arr() eg. result of ft_split()\n");
	while (arr[i] != NULL)
	{
		printf("%d: %s\n", i, arr[i]);
		i++;
	}
}

int	load_mandatory_scene(char *mapfile, t_scene *scene)
{
	int		map_fd;

	map_fd = open(mapfile, O_RDONLY);
	if (map_fd == -1)
	{
		ft_putstr_fd("Error\nMap cannot be opened\n", 2);
		return (-1);
	}
	if (load_scene_details(map_fd, &scene) == -1 || prepare_walls(&scene) == -1
		|| is_six_details_valid(scene) == -1)
		return (-1);
	scene->hex_floor = convert_rgb_array_to_int(scene->floor);
	scene->hex_ceiling = convert_rgb_array_to_int(scene->ceiling);
	if (is_mandatory_map_char_valid(scene->tmp_map_buf) == -1 || \
		process_map(scene) == -1 || \
		is_mandatory_map_valid(scene) == -1)
		return (-1);
	return (0);
}

int	is_mandatory_map_char_valid(char *s)
{
	const char	ref[] = " \n10NSEW";
	int			i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(ref, s[i]) == NULL)
		{
			ft_putstr_fd("Error\nInvalid map char\n", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	is_mandatory_map_valid(t_scene *scene)
{
	if (is_num_player_valid(scene->map) == -1 || \
		load_player_pos(scene->map, scene) == -1)
		return (-1);
	ff_mandatory(scene->p_pos.y, scene->p_pos.x, scene);
	if (is_fill_char_at_map_border(scene) == 0)
		return (-1);
	return (0);
}

/*
NOTE. ff is short for flood fill

if out of bounds row-wise, return
if out of bounds col-wise, return
if char at current pos: is wall '1', or fill 'F', return
if char at current pos: is empty '0', or valid (player) char, replace with 'F'
try to ff() the four cardinal directions, relative to current char pos
*/
void	ff_mandatory(int i, int j, t_scene *s)
{
	if (i < 0 || i > s->map_dim.y - 1)
		return ;
	if (j < 0 || j > s->map_dim.x - 1)
		return ;
	if (s->map_bak[i][j] == '1' || s->map_bak[i][j] == 'F')
		return ;
	if (s->map_bak[i][j] == '0' || ft_strchr("NSEW", s->map_bak[i][j]))
		s->map_bak[i][j] = 'F';
	ff_mandatory(i + 1, j, s);
	ff_mandatory(i - 1, j, s);
	ff_mandatory(i, j + 1, s);
	ff_mandatory(i, j - 1, s);
}

/*
for t_scene struct,
checks if alloc~ed elements are present, and if so, free() them!

NOTE. no need to free() the t_scene elements that are NOT alloc~ed

void	free_scene_struct(t_scene *s)
{
	if (s->no != NULL)
		free(s->no);
	if (s->so != NULL)
		free(s->so);
	if (s->ea != NULL)
		free(s->ea);
	if (s->we != NULL)
		free(s->we);
	if (s->floor != NULL)
		free(s->floor);
	if (s->ceiling != NULL)
		free(s->ceiling);
	if (s->tmp_map_buf != NULL)
		free(s->tmp_map_buf);
	if (s->map != NULL)
		free_char_map(s->map);
	if (s->map_bak != NULL)
		free_char_map(s->map_bak);
}

to do 01 Nov 2024

# split functions in validate_input.c into separate .c files
*/
