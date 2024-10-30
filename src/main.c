/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:44:00 by jaslim            #+#    #+#             */
/*   Updated: 2024/10/31 01:19:09 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
#include "../inc/validate_input.h"

void	ft_destroy_image(void *mlx_ptr, t_img *img)
{
	if (mlx_ptr && img->img)
		mlx_destroy_image(mlx_ptr, img->img);
	img->img = NULL;
}

void	free_int_array(int	**output, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_free_void((void **)&output[i]);
		i++;
	}
	free(output);
}

int	cleanup(t_game *game, unsigned char status, char *msg)
{
	int	i;

	mlx_do_key_autorepeaton(game->mlx);
	i = 0;
	while (i < IMG_MAX)
	{
		ft_destroy_image(game->mlx, &game->img[i]);
		i++;
	}
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	game->win = NULL;
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	ft_free_void(&game->mlx);
	ft_free_void((void **)&game->item.arr);
	ft_free(&game->frame.fps_str);
	free_int_array(game->map.arr, game->map.size.y);
	if (msg)
		ft_putstr_fd(msg, 2);
	exit(status);
}

int	init_img(void *mlx_ptr, t_img *img, int width, int height)
{
	img->img = mlx_new_image(mlx_ptr, width, height);
	if (img->img == NULL)
	{
		img->addr = NULL;
		return (-1);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_len, &img->endian);
	if (img->addr == NULL)
		return (-1);
	img->size.x = width;
	img->size.y = height;
	return (0);
}

// Sets a pixel in the img address to a specified color in hexadecimal format.
void	set_pixel(t_img *img, int x, int y, unsigned int color)
{
	const int	step = (img->bits_per_pixel / 8);
	char		*dst;

	if (x < 0 || y < 0 || x >= img->size.x || y >= img->size.y)
		return ;
	dst = img->addr + ((y * img->line_len) + x * step);
	*(unsigned int *)dst = color;
}

// Sets a pixel in the img address to a specified color in hexadecimal format.
// Ignores transparent pixels, as well as MAGENTA (0xFF00FF).
void	set_pixel_alpha(t_img *img, int x, int y, unsigned int color)
{
	const int	step = (img->bits_per_pixel / 8);
	char		*dst;

	if (x < 0 || y < 0 || x >= img->size.x || y >= img->size.y
		|| (color >> 24) & 0xFF || color == MAGENTA)
		return ;
	dst = img->addr + ((y * img->line_len) + x * step);
	*(unsigned int *)dst = color;
}

// Returns a pixel's color in the img address.
unsigned int	get_pixel(t_img *img, int x, int y)
{
	const int	step = (img->bits_per_pixel / 8);
	char		*src;

	src = img->addr + ((y * img->line_len) + x * step);
	return (*(unsigned int *)src);
}

void	put_img_scale_mid(t_point ofs, t_img *src, t_img *dst, t_fpoint scale)
{
	t_fpoint	sp;
	t_point		dp;
	t_point		s_mid;

	scale.x = 1.0 / scale.x;
	scale.y = 1.0 / scale.y;
	s_mid.x = src->size.x * 0.5;
	s_mid.y = src->size.y * 0.5;
	dp.y = 0;
	while (dp.y < dst->size.y)
	{
		dp.x = 0;
		while (dp.x < dst->size.x)
		{
			sp.x = (dp.x - ofs.x - dst->size.x * 0.5) * scale.x + s_mid.x;
			sp.y = (dp.y - ofs.y - dst->size.y * 0.5) * scale.y + s_mid.y;
			if (sp.x >= 0 && sp.x < src->size.x
				&& sp.y >= 0 && sp.y < src->size.y)
				set_pixel_alpha(dst, dp.x, dp.y,
					get_pixel(src, sp.x, sp.y));
			dp.x++;
		}
		dp.y++;
	}
}

// Darkens a color in hexadecimal format, by a specified factor. (1.0 to 0.0)
// The closer the factor is to 0, the closer to black it becomes.
unsigned int	darken(unsigned int color, float factor)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if ((color >> 24) & 0xFF)
		return (color);
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = (color >> 0) & 0xFF;
	r *= factor;
	g *= factor;
	b *= factor;
	return ((r << 16) | (g << 8) | b);
}

void	put_img_scale_darken(t_point ofs, t_img *src, t_img *dst,
	t_fpoint scale)
{
	t_fpoint	sp;
	t_point		dp;
	t_point		s_mid;

	scale.x = 1.0 / scale.x;
	scale.y = 1.0 / scale.y;
	s_mid.x = src->size.x * 0.5;
	s_mid.y = src->size.y * 0.5;
	dp.y = 0;
	while (dp.y < dst->size.y)
	{
		dp.x = 0;
		while (dp.x < dst->size.x)
		{
			sp.x = (dp.x - ofs.x - dst->size.x * 0.5) * scale.x + s_mid.x;
			sp.y = (dp.y - ofs.y - dst->size.y * 0.5) * scale.y + s_mid.y;
			if (sp.x >= 0 && sp.x < src->size.x
				&& sp.y >= 0 && sp.y < src->size.y)
				set_pixel_alpha(dst, dp.x, dp.y,
					darken(get_pixel(src, sp.x, sp.y), src->intensity));
			dp.x++;
		}
		dp.y++;
	}
}

void	put_img_scale_mid_bot(t_point ofs, t_img *src, t_img *dst,
	t_fpoint scale)
{
	t_fpoint	sp;
	t_point		dp;
	t_point		s_mid;

	scale.x = 1.0 / scale.x;
	scale.y = 1.0 / scale.y;
	s_mid.x = src->size.x * 0.5;
	s_mid.y = -src->size.x;
	dp.y = 0;
	while (dp.y < dst->size.y)
	{
		dp.x = 0;
		while (dp.x < dst->size.x)
		{
			sp.x = (dp.x - ofs.x - dst->size.x * 0.5) * scale.x + s_mid.x;
			sp.y = (dp.y - ofs.y - dst->size.y * 0.5) * scale.y + s_mid.y;
			if (sp.x >= 0 && sp.x < src->size.x
				&& sp.y >= 0 && sp.y < src->size.y)
				set_pixel_alpha(dst, dp.x, dp.y,
					get_pixel(src, sp.x, sp.y));
			dp.x++;
		}
		dp.y++;
	}
}

void	put_img_scale(t_point offset, t_img *src, t_img *dst, t_fpoint scale)
{
	t_fpoint	src_pos;
	t_point		dst_pos;

	scale.x = 1.0 / scale.x;
	scale.y = 1.0 / scale.y;
	dst_pos.y = 0;
	while (dst_pos.y < dst->size.y)
	{
		dst_pos.x = 0;
		while (dst_pos.x < dst->size.x)
		{
			src_pos.x = (dst_pos.x - offset.x) * scale.x;
			src_pos.y = (dst_pos.y - offset.y) * scale.y;
			if (src_pos.x >= 0 && src_pos.x < src->size.x
				&& src_pos.y >= 0 && src_pos.y < src->size.y)
				set_pixel_alpha(dst, dst_pos.x, dst_pos.y,
					get_pixel(src, src_pos.x, src_pos.y));
			dst_pos.x++;
		}
		dst_pos.y++;
	}
}

// Draw an img to another img by rewriting parts the src addr with dst addr.
void	put_img(t_point offset, t_img *src, t_img *dst)
{
	t_point	src_pos;
	t_point	dst_pos;

	src_pos.y = 0;
	while (src_pos.y < src->size.y)
	{
		src_pos.x = 0;
		while (src_pos.x < src->size.x)
		{
			dst_pos.x = src_pos.x + offset.x;
			dst_pos.y = src_pos.y + offset.y;
			if (dst_pos.x >= 0 && dst_pos.x < dst->size.x
				&& dst_pos.y >= 0 && dst_pos.y < dst->size.y)
				set_pixel_alpha(dst, dst_pos.x, dst_pos.y,
					get_pixel(src, src_pos.x, src_pos.y));
			src_pos.x++;
		}
		src_pos.y++;
	}
}

// Attempts to load and store an xpm file.
// Returns (0) upon success, and (0) upon failure.
int	load_xpm(void *mlx, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(mlx, path, &img->size.x, &img->size.y);
	if (!img->img)
		return (1);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_len, &img->endian);
	return (0);
}

int	load_pwl_xpms(t_game *game)
{
	if (load_xpm(game->mlx, "textures/pwl0.xpm", &game->img[T_PWL0])
		|| load_xpm(game->mlx, "textures/pwl1.xpm", &game->img[T_PWL1])
		|| load_xpm(game->mlx, "textures/pwl2.xpm", &game->img[T_PWL2])
		|| load_xpm(game->mlx, "textures/pwl3.xpm", &game->img[T_PWL3])
		|| load_xpm(game->mlx, "textures/pwl4.xpm", &game->img[T_PWL4])
		|| load_xpm(game->mlx, "textures/pwl5.xpm", &game->img[T_PWL5])
		|| load_xpm(game->mlx, "textures/pwl6.xpm", &game->img[T_PWL6])
		|| load_xpm(game->mlx, "textures/pwl7.xpm", &game->img[T_PWL7])
		|| load_xpm(game->mlx, "textures/pwl_arm0.xpm", &game->img[T_PWL_ARM0])
		|| load_xpm(game->mlx, "textures/pwl_arm1.xpm", &game->img[T_PWL_ARM1])
		|| load_xpm(game->mlx, "textures/pwl_arm2.xpm", &game->img[T_PWL_ARM2])
		|| load_xpm(game->mlx, "textures/pwl_arm3.xpm", &game->img[T_PWL_ARM3])
		|| load_xpm(game->mlx, "textures/pwl_arm4.xpm", &game->img[T_PWL_ARM4])
		|| load_xpm(game->mlx, "textures/pwl_arm5.xpm", &game->img[T_PWL_ARM5])
		|| load_xpm(game->mlx, "textures/pwl_arm6.xpm", &game->img[T_PWL_ARM6]))
		return (1);
	return (0);
}

int	load_xpms(t_game *game)
{
	if (load_xpm(game->mlx, "textures/wall/wall1.xpm", &game->img[T_NORTH])
		|| load_xpm(game->mlx, "textures/wall/wall2.xpm", &game->img[T_SOUTH])
		|| load_xpm(game->mlx, "textures/wall/wall3.xpm", &game->img[T_EAST])
		|| load_xpm(game->mlx, "textures/wall/wall4.xpm", &game->img[T_WEST])
		|| load_xpm(game->mlx, "textures/door.xpm", &game->img[T_DOOR_CLOSE])
		|| load_xpm(game->mlx, "textures/shift_tab.xpm", &game->img[T_PAUSE])
		|| load_xpm(game->mlx, "textures/bg_dither.xpm", &game->img[T_DITHER])
		|| load_xpm(game->mlx, "textures/xeno0.xpm", &game->img[T_XENO0])
		|| load_xpm(game->mlx, "textures/xeno1.xpm", &game->img[T_XENO1])
		|| load_xpm(game->mlx, "textures/xeno2.xpm", &game->img[T_XENO2])
		|| load_xpm(game->mlx, "textures/xeno3.xpm", &game->img[T_XENO3])
		|| load_xpm(game->mlx, "textures/xeno4.xpm", &game->img[T_XENO4])
		|| load_xpm(game->mlx, "textures/xeno5.xpm", &game->img[T_XENO5])
		|| load_xpm(game->mlx, "textures/xeno6.xpm", &game->img[T_XENO6])
		|| load_xpm(game->mlx, "textures/xeno7.xpm", &game->img[T_XENO7])
		|| load_xpm(game->mlx, "textures/item.xpm", &game->img[T_ITEM]))
		return (-1);
	if (load_pwl_xpms(game))
		return (-1);
	return (0);
}

void	draw_rectangle(t_img *dst, t_point origin, t_point size,
	unsigned int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			set_pixel_alpha(dst, x + origin.x, y + origin.y, color);
			x++;
		}
		y++;
	}
}

void	draw_circle(t_img *dst, t_point origin, int radius, unsigned int color)
{
	int		r_sq;
	t_point	p;
	t_point	d;

	r_sq = radius * radius;
	p.y = origin.y - radius;
	while (p.y <= origin.y + radius)
	{
		p.x = origin.x - radius;
		while (p.x <= origin.x + radius)
		{
			d.x = p.x - origin.x;
			d.y = p.y - origin.y;
			if ((d.x * d.x) + (d.y * d.y) <= r_sq)
				set_pixel_alpha(dst, p.x, p.y, color);
			p.x++;
		}
		p.y++;
	}
}

void	draw_circle_outline(t_img *dst, t_point origin, int radius,
	unsigned int color)
{
	int		r_sq;
	t_point	p;
	t_point	d;

	r_sq = radius * radius;
	p.y = origin.y - radius;
	while (p.y <= origin.y + radius)
	{
		p.x = origin.x - radius;
		while (p.x <= origin.x + radius)
		{
			d.x = p.x - origin.x;
			d.y = p.y - origin.y;
			if ((d.x * d.x) + (d.y * d.y) >= r_sq - radius + 1
				&& (d.x * d.x) + (d.y * d.y) <= r_sq + radius - 1)
				set_pixel_alpha(dst, p.x, p.y, color);
			p.x++;
		}
		p.y++;
	}
}

void	brasenham(int *err, t_point *start, t_point d, t_point s)
{
	if (2 * *err > -d.x)
	{
		*err -= d.y;
		start->x += s.x;
	}
	if (2 * *err < d.y)
	{
		*err += d.x;
		start->y += s.y;
	}
}

void	draw_line(t_img *img, t_point start, t_point end, unsigned int color)
{
	int		max;
	t_point	d;
	t_point	s;
	int		err;

	d.x = ft_abs(end.x - start.x);
	d.y = ft_abs(end.y - start.y);
	s.x = -1;
	s.y = -1;
	if (start.x < end.x)
		s.x = 1;
	if (start.y < end.y)
		s.y = 1;
	err = -d.y;
	if (d.x > d.y)
		err = d.x;
	err *= 0.5;
	max = 1000;
	while ((start.x != end.x || start.y != end.y) && max > 0)
	{
		brasenham(&err, &start, d, s);
		set_pixel_alpha(img, start.x, start.y, color);
		max--;
	}
}

void	draw_diagonal_lines(t_img *img, t_point size, unsigned int color)
{
	t_point	start;
	t_point	end;
	int		i;
	int		step;

	step = 16;
	i = -size.x;
	while (i < size.x * 2)
	{
		start = (t_point){i, -1};
		end = (t_point){i + size.x, size.y - 1};
		draw_line(img, start, end, color);
		i += step;
	}
}

void	draw_map_player(t_img *img, t_player p)
{
	t_point			player_pos;
	t_point			pointer_pos;
	float			dir_radius;
	float			dir_dist;

	player_pos.x = (int)((p.pos.x * (float)MAP_CELL_SIZE));
	player_pos.y = (int)((p.pos.y * (float)MAP_CELL_SIZE));
	draw_circle(img, player_pos, MAP_CELL_SIZE * 0.15, WHITE);
	draw_circle_outline(img, player_pos, MAP_CELL_SIZE * 0.25, WHITE);
	dir_radius = MAP_CELL_SIZE * 0.15;
	dir_dist = 0.25;
	pointer_pos.x = (int)((p.pos.x + (p.dir.x * dir_dist * p.zoom))
			* (float)MAP_CELL_SIZE);
	pointer_pos.y = (int)((p.pos.y + (p.dir.y * dir_dist * p.zoom))
			* (float)MAP_CELL_SIZE);
	draw_circle(img, pointer_pos, dir_radius, WHITE);
}

int	validate_input(int ac, char **av, t_scene *scene)
{	
	if (check_n_cmdline_args(ac) == -1)
		return (-1);
	if (is_map_a_dot_cub_file(av[1]) == -1)
		return (-1);
	if (is_map_file_openable(av[1]) == -1)
		return (-1);
	if (load_scene(av[1], scene) == -1)
		return (-1);
	return (0);
}
/*
last updated 24 Oct 2024
restart at trim_tmp_map_buf() in validate_input.c

next task: check for empty line(s) in between map lines, in tmp_map_buf
with ft_strnstr

*/

// void	ft_destroy_image(void *mlx_ptr, void **img)
// {
// 	if (mlx_ptr && img && *img)
// 		mlx_destroy_image(mlx_ptr, *img);
// 	*img = NULL;
// }

// int	cleanup(t_game *game, unsigned char status, char *msg)
// {
// 	ft_destroy_image(game->mlx_ptr, &game->img.misc[0].img);
// 	ft_destroy_image(game->mlx_ptr, &game->img.win.img);
// 	ft_destroy_image(game->mlx_ptr, &game->img.map.img);
// 	ft_destroy_image(game->mlx_ptr, &game->img.map_mask.img);
// 	ft_destroy_image(game->mlx_ptr, &game->img.map_bg.img);
// 	ft_destroy_image(game->mlx_ptr, &game->img.ceiling.img);
// 	ft_destroy_image(game->mlx_ptr, &game->img.floor.img);
// 	if (game->win_ptr)
// 		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
// 	game->win_ptr = NULL;
// 	if (game->mlx_ptr)
// 		mlx_destroy_display(game->mlx_ptr);
// 	ft_free_void(&game->mlx_ptr);
// 	ft_free(&game->frame.fps_str);
// 	if (msg)
// 		ft_putstr_fd(msg, 2);
// 	exit(status);
// }

t_point	center(t_point origin, t_point size)
{
	origin.x -= size.x * 0.5;
	origin.y -= size.y * 0.5;
	return (origin);
}

int	init_bg(t_game *game, int ceiling, int floor)
{
	t_point	size;

	size.x = RES_X;
	size.y = RES_Y;
	if (init_img(game->mlx, &game->img[T_CEILING], RES_X, RES_Y) == -1
		|| init_img(game->mlx, &game->img[T_FLOOR], RES_X, RES_Y) == -1)
		return (-1);
	draw_rectangle(&game->img[T_CEILING], (t_point){0, 0}, size, ceiling);
	draw_rectangle(&game->img[T_FLOOR], (t_point){0, 0}, size, floor);
	return (0);
}

void	draw_tile(t_img *map, t_point origin, int tile)
{
	const t_point	size = (t_point){MAP_CELL_SIZE - 1, MAP_CELL_SIZE - 1};

	if (tile == 2)
		draw_rectangle(map, (t_point){origin.x + MAP_CELL_SIZE * 0.3,
			origin.y + MAP_CELL_SIZE * 0.3},
			(t_point){MAP_CELL_SIZE * 0.3, MAP_CELL_SIZE * 0.3}, BLACK);
	else if (tile == -2)
		draw_rectangle(map, (t_point){origin.x + MAP_CELL_SIZE * 0.1,
			origin.y + MAP_CELL_SIZE * 0.1},
			(t_point){MAP_CELL_SIZE * 0.8, MAP_CELL_SIZE * 0.8}, BLACK);
	else if (tile <= 0)
		draw_rectangle(map, origin, size, BLACK);
	if (tile == -3)
		draw_circle(map, (t_point){origin.x + MAP_CELL_SIZE * 0.5 - 1,
			origin.y + MAP_CELL_SIZE * 0.5 - 1},
			MAP_CELL_SIZE * 0.25, 0xFFAD1A);
}

void	update_map_tiles(t_game *game)
{
	t_point	count;
	t_point	origin;

	draw_rectangle(&game->img[T_MAP_TILES], (t_point){0, 0},
		game->img[T_MAP_TILES].size, MAP_COLOR);
	count.y = 0;
	origin.y = 0;
	while (count.y < game->map.size.y)
	{
		origin.x = 0;
		count.x = 0;
		while (count.x < game->map.size.x)
		{
			draw_tile(&game->img[T_MAP_TILES], origin,
				game->map.arr[count.y][count.x]);
			count.x++;
			origin.x += MAP_CELL_SIZE;
		}
		count.y++;
		origin.y += MAP_CELL_SIZE;
	}
	game->map.update = 0;
}

// Fill an img with a specified color in hexadecimal format.
void	fill_img(t_img *img, unsigned int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->size.y)
	{
		x = 0;
		while (x < img->size.x)
		{
			set_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	convert_row_to_ints(int *output_row, char *input_row)
{
	int	x;

	x = 0;
	while (input_row[x])
	{
		if (input_row[x] == '1')
			output_row[x] = 1;
		else if (input_row[x] == 'D')
			output_row[x] = 2;
		else if (input_row[x] == 'P')
			output_row[x] = 3;
		else if (input_row[x] == 'C')
			output_row[x] = -3;
		else
			output_row[x] = 0;
		x++;
	}
}

int	**char_to_int_map(char **input)
{
	t_point	it;
	int		num_strings;
	int		**output;

	num_strings = ft_count_strings(input);
	output = ft_calloc(num_strings, sizeof(int *));
	if (!output)
		return (NULL);
	it.y = 0;
	while (it.y < num_strings)
	{
		output[it.y] = ft_calloc(ft_strlen(input[it.y]), sizeof(int));
		if (!output[it.y])
		{
			free_int_array(output, it.y);
			return (NULL);
		}
		convert_row_to_ints(output[it.y], input[it.y]);
		it.y++;
	}
	return (output);
}

int	init_minimap(t_game *game, t_point map_grid_size)
{
	t_point	map;
	t_point	mask;

	map.x = map_grid_size.x * MAP_CELL_SIZE;
	map.y = map_grid_size.y * MAP_CELL_SIZE;
	mask.x = 16 * MAP_CELL_SIZE * 0.5;
	mask.y = 16 * MAP_CELL_SIZE * 0.5;
	if (init_img(game->mlx, &game->img[T_MAP], map.x, map.y) == -1
		|| init_img(game->mlx, &game->img[T_MAP_ENEMY_PATH], map.x, map.y) == -1
		|| init_img(game->mlx, &game->img[T_MAP_TILES], map.x, map.y) == -1
		|| init_img(game->mlx, &game->img[T_MAP_MASK], mask.x, mask.y) == -1
		|| init_img(game->mlx, &game->img[T_MAP_BG], mask.x, mask.y) == -1)
		return (-1);
	game->map.arr = char_to_int_map(game->scene.map);
	game->map.size.x = game->scene.map_dim.x;
	game->map.size.y = game->scene.map_dim.y;
	fill_img(&game->img[T_MAP_ENEMY_PATH], MAGENTA);
	game->map.offset.x = RES_X2 - game->img[T_MAP_MASK].size.x * 0.5;
	game->map.offset.y = RES_Y - game->img[T_MAP_MASK].size.x - MAP_CELL_SIZE;
	draw_rectangle(&game->img[T_MAP_BG], (t_point){0, 0},
		game->img[T_MAP_MASK].size, BLACK);
	draw_diagonal_lines(&game->img[T_MAP_BG],
		game->img[T_MAP_MASK].size, 0x333333);
	update_map_tiles(game);
	return (0);
}

int	exit_game(t_game *game)
{
	cleanup(game, 0, "exit\n");
	return (0);
}

void	toggle_mouse(t_game *game)
{
	t_point	center;

	center.x = RES_X2;
	center.y = RES_Y2;
	if (game->state[S_MOUSE] == 0)
		mlx_mouse_move(game->mlx, game->win, center.x, center.y);
	game->state[S_MOUSE] = !game->state[S_MOUSE];
}

void	pause_game(t_game *game)
{
	t_point	center;

	center.x = RES_X2;
	center.y = RES_Y2;
	if (game->state[S_RUN])
		game->state[S_PAUSE] = !game->state[S_PAUSE];
	if (!game->state[S_PAUSE] && game->state[S_MOUSE])
		mlx_mouse_move(game->mlx, game->win, center.x, center.y);
}

void	handle_keystate(unsigned int key, int state, t_game *game)
{
	if (key == XK_Up || key == XK_w)
		game->state[S_UP] = state;
	if (key == XK_Down || key == XK_s)
		game->state[S_DOWN] = state;
	if (key == XK_a)
		game->state[S_LEFT] = state;
	if (key == XK_d)
		game->state[S_RIGHT] = state;
	if (key == XK_r)
		game->state[S_ROT_U] = state;
	if (key == XK_f)
		game->state[S_ROT_D] = state;
	if (key == XK_Left)
		game->state[S_ROT_L] = state;
	if (key == XK_Right)
		game->state[S_ROT_R] = state;
	if (key == XK_Shift_L)
		game->state[S_RUN] = state;
	if (key == XK_Control_L)
		game->state[S_SPACE] = state;
	if (key == XK_e)
		game->state[S_INTERACT] = state;
}

int	key_release(unsigned int key, t_game *game)
{
	handle_keystate(key, 0, game);
	return (0);
}

int	out_of_bounds(t_fpoint map, t_game *game)
{
	if (map.x < 0 || map.y < 0
		|| map.x >= game->map.size.x || map.y >= game->map.size.y)
		return (1);
	return (0);
}

// Determines the traversal direction,
// by comparing the distance a ray has to traverse, during a dda cycle.
void	set_dda_step_side(t_ray *r)
{
	if (r->side_dist.x < r->side_dist.y)
	{
		r->side_dist.x += r->delta_dist.x;
		r->map.x += r->step.x;
		r->side = VERTICAL;
	}
	else
	{
		r->side_dist.y += r->delta_dist.y;
		r->map.y += r->step.y;
		r->side = HORIZONTAL;
	}
}

int	dda_interact(t_ray *r, t_game *game)
{
	int	i;
	int	tile_hit;

	i = 0;
	while (i < 3)
	{
		set_dda_step_side(r);
		if (out_of_bounds(r->map, game))
			return (0);
		tile_hit = game->map.arr[(int)r->map.y][(int)r->map.x];
		if (tile_hit == TILE_WALL)
			return (0);
		if (!out_of_bounds(r->map, game)
			&& (tile_hit == TILE_PWL || tile_hit == TILE_DOOR
				|| tile_hit == TILE_DOOR_OPEN))
			return (game->map.arr[(int)r->map.y][(int)r->map.x]);
		i++;
	}
	return (0);
}

// Sets a rays direction, based on the player direction vector.
// camera_x determines the angle in which ray originates from.
// < 0: left of center, 0: center, > 0: right of center
// flag for zoom can be enabled to include the players zoom in the calculation.
void	set_ray_direction(t_game *game, t_ray *r, float camera_x, int incl_zoom)
{
	float	zoom;

	r->map.x = (int)game->player.pos.x;
	r->map.y = (int)game->player.pos.y;
	zoom = game->player.zoom;
	if (!incl_zoom)
		zoom = 1;
	r->dir.x = game->player.dir.x * zoom
		+ game->player.plane.x * camera_x;
	r->dir.y = game->player.dir.y * zoom
		+ game->player.plane.y * camera_x;
	if (r->dir.x == 0)
		r->delta_dist.x = 1E+37;
	else
		r->delta_dist.x = fabsf(1 / r->dir.x);
	if (r->dir.y == 0)
		r->delta_dist.y = 1E+37;
	else
		r->delta_dist.y = fabsf(1 / r->dir.y);
}

// Determine the ray's array traversal direction (up, down, left, or right),
// and how far it should increment itself in the array.
void	set_ray_step_direction(t_game *game, t_ray *r)
{
	if (r->dir.x < 0)
	{
		r->step.x = -1;
		r->side_dist.x = (game->player.pos.x - r->map.x) * r->delta_dist.x;
	}
	else
	{
		r->step.x = 1;
		r->side_dist.x = (r->map.x + 1.0 - game->player.pos.x)
			* r->delta_dist.x;
	}
	if (r->dir.y < 0)
	{
		r->step.y = -1;
		r->side_dist.y = (game->player.pos.y - r->map.y) * r->delta_dist.y;
	}
	else
	{
		r->step.y = 1;
		r->side_dist.y = (r->map.y + 1.0 - game->player.pos.y)
			* r->delta_dist.y;
	}
}

// Unstucks the player by pushing them,
// if it's radius would be within a door after one closes.
void	unstuck_player(t_game *game, t_ray r)
{
	t_point	pos;

	pos.x = (int)game->player.pos.x - (int)r.map.x;
	pos.y = (int)game->player.pos.y - (int)r.map.y;
	if (pos.x == -1)
		game->player.pos = (t_fpoint){game->player.pos.x - PLAYER_RADIUS,
			game->player.pos.y};
	if (pos.x == 1)
		game->player.pos = (t_fpoint){game->player.pos.x + PLAYER_RADIUS,
			game->player.pos.y};
	if (pos.y == -1)
		game->player.pos = (t_fpoint){game->player.pos.x,
			game->player.pos.y - PLAYER_RADIUS};
	if (pos.y == 1)
		game->player.pos = (t_fpoint){game->player.pos.x,
			game->player.pos.y + PLAYER_RADIUS};
}

// Displays a button prompt at the center of the screen.
void	display_ui_msg(t_game *game, char *key, char *msg)
{
	int	msg_y;

	msg_y = 0;
	if (key)
		msg_y = 15;
	draw_circle_outline(&game->img[T_WIN],
		(t_point){RES_X2, RES_Y2}, 25, WHITE);
	if (key)
		mlx_string_put(game->mlx, game->win, RES_X2 + 34,
			RES_Y2, WHITE, key);
	mlx_string_put(game->mlx, game->win, RES_X2 + 34,
		RES_Y2 + msg_y, WHITE, msg);
}

void	interact_door(t_game *game, t_ray r)
{
	game->map.arr[(int)r.map.y][(int)r.map.x]
		= -game->map.arr[(int)r.map.y][(int)r.map.x];
	if (r.wall_dist <= PLAYER_RADIUS)
		unstuck_player(game, r);
	game->state[S_INTERACT] = 0;
	game->map.update = 1;
}

void	interact_pwl(t_game *game)
{
	if (game->item.collected < REQUIRED_ITEMS)
		return ;
	game->map.arr[(int)game->pwl.item.pos.y][(int)game->pwl.item.pos.x] = 0;
	game->player.pos = game->pwl.item.pos;
	game->player.dir.x = -0.7071;
	game->player.dir.y = 0.7071;
	game->player.plane.x = -game->player.dir.y * 0.66;
	game->player.plane.y = game->player.dir.x * 0.66;
	game->player.z = 0.3;
	game->player.pitch = 100;
	game->pwl.item.collected = 1;
	game->map.update = 1;
}

void	check_interact(t_game *game, int *tile_hit, t_ray *r)
{
	set_ray_direction(game, r, 0, 0);
	set_ray_step_direction(game, r);
	*tile_hit = dda_interact(r, game);
	if (*tile_hit == 0)
		return ;
	if (r->side == VERTICAL)
		r->wall_dist = r->side_dist.x - r->delta_dist.x;
	else
		r->wall_dist = r->side_dist.y - r->delta_dist.y;
	if (r->wall_dist < 2.0 && !game->state[S_MAP_BIG])
	{
		if (*tile_hit == TILE_DOOR || *tile_hit == TILE_DOOR_OPEN)
			display_ui_msg(game, "[E]", UI_DOOR);
		if (*tile_hit == TILE_PWL)
		{
			if (game->item.collected < REQUIRED_ITEMS)
				display_ui_msg(game, NULL, UI_PWL_FALSE);
			else
				display_ui_msg(game, "[E]", UI_PWL_TRUE);
		}
	}
}

void	interact(t_game *game)
{
	t_ray	r;
	int		tile_hit;

	check_interact(game, &tile_hit, &r);
	if (game->state[S_INTERACT] == 1)
	{
		if (tile_hit == TILE_DOOR || tile_hit == TILE_DOOR_OPEN)
			return (interact_door(game, r));
		if (tile_hit == TILE_PWL)
			interact_pwl(game);
	}
}

int	key_press(unsigned int key, t_game *game)
{
	handle_keystate(key, 1, game);
	if (key == XK_Tab)
		pause_game(game);
	if (key == XK_Escape)
		exit_game(game);
	if (key == XK_p)
		toggle_mouse(game);
	if (key == XK_m)
		game->state[S_MAP_DISABLE] = !game->state[S_MAP_DISABLE];
	if (key == XK_1)
	{
		game->state[S_MAP_DISABLE] = 0;
		game->state[S_MAP_BIG] = !game->state[S_MAP_BIG];
	}
	if (key == XK_2)
		game->state[S_ENEMY_PATH] = !game->state[S_ENEMY_PATH];
	if (game->pwl.item.collected == 1 && key == XK_space)
		game->state[S_PUNCHING] = 1;
	return (0);
}

void	vertical_look(t_game *game, float delta)
{
	const int	limit = RES_Y2;
	int			new;

	new = game->player.pitch + delta;
	if (new >= -limit && new <= limit)
		game->player.pitch += delta;
	if (game->player.pitch < -limit)
		game->player.pitch = -limit;
	else if (game->player.pitch > limit)
		game->player.pitch = limit;
}

void	handle_mouselook(t_game *game)
{
	const t_point	center = {RES_X2, RES_Y2};
	t_point			mouse;
	float			old_dir_x;
	float			old_plane_x;
	t_point			delta;

	mlx_mouse_get_pos(game->mlx, game->win, &mouse.x, &mouse.y);
	delta.x = mouse.x - center.x;
	delta.y = mouse.y - center.y;
	if (delta.x != 0 || delta.y != 0)
	{
		old_dir_x = game->player.dir.x;
		old_plane_x = game->player.plane.x;
		game->player.dir.x = game->player.dir.x * cos(MOUSE_SEN * delta.x)
			- game->player.dir.y * sin(MOUSE_SEN * delta.x);
		game->player.dir.y = old_dir_x * sin(MOUSE_SEN * delta.x)
			+ game->player.dir.y * cos(MOUSE_SEN * delta.x);
		game->player.plane.x = game->player.plane.x * cos(MOUSE_SEN * delta.x)
			- game->player.plane.y * sin(MOUSE_SEN * delta.x);
		game->player.plane.y = old_plane_x * sin(MOUSE_SEN * delta.x)
			+ game->player.plane.y * cos(MOUSE_SEN * delta.x);
		vertical_look(game, delta.y);
		mlx_mouse_move(game->mlx, game->win, center.x, center.y);
	}
}

void	calculate_movement(t_game *game, float *move_x, float *move_y)
{
	if (game->state[S_UP])
	{
		*move_x += game->player.dir.x;
		*move_y += game->player.dir.y;
	}
	if (game->state[S_DOWN])
	{
		*move_x -= game->player.dir.x;
		*move_y -= game->player.dir.y;
	}
	if (game->state[S_LEFT])
	{
		*move_x += game->player.dir.y;
		*move_y -= game->player.dir.x;
	}
	if (game->state[S_RIGHT])
	{
		*move_x -= game->player.dir.y;
		*move_y += game->player.dir.x;
	}
}

void	normalize_movement(float *move_x, float *move_y)
{
	float	len_sq;
	float	normalized_speed;

	len_sq = (*move_x * *move_x) + (*move_y * *move_y);
	if (len_sq > 0)
	{
		normalized_speed = 1.0 / sqrt(len_sq);
		*move_x *= normalized_speed;
		*move_y *= normalized_speed;
	}
}

int	check_collision(t_fpoint *pos, t_fpoint new_pos, float radius, t_game *game)
{
	t_fpoint	side;
	int			collision;

	collision = 0;
	if (new_pos.x - pos->x < 0)
		side.x = -radius;
	else
		side.x = radius;
	if (new_pos.y - pos->y < 0)
		side.y = -radius;
	else
		side.y = radius;
	if (game->map.arr[(int)(pos->y)][(int)(new_pos.x - radius)] < 1
		&& game->map.arr[(int)(pos->y - radius)][(int)(new_pos.x + side.x)] < 1
		&& game->map.arr[(int)(pos->y + radius)][(int)(new_pos.x + side.x)] < 1)
		pos->x = new_pos.x;
	else
		collision = 1;
	if (game->map.arr[(int)(new_pos.y - radius)][(int)(pos->x)] < 1
		&& game->map.arr[(int)(new_pos.y + side.y)][(int)(pos->x - radius)] < 1
		&& game->map.arr[(int)(new_pos.y + side.y)][(int)(pos->x + radius)] < 1)
		pos->y = new_pos.y;
	else
		collision = 1;
	return (collision);
}

void	handle_movement_xy(t_game *game, float speed)
{
	t_fpoint	move;
	t_fpoint	new_pos;

	if (!game->state[S_UP] && !game->state[S_DOWN]
		&& !game->state[S_LEFT] && !game->state[S_RIGHT])
		return ;
	move.x = 0;
	move.y = 0;
	calculate_movement(game, &move.x, &move.y);
	normalize_movement(&move.x, &move.y);
	new_pos.x = game->player.pos.x + move.x * speed;
	new_pos.y = game->player.pos.y + move.y * speed;
	check_collision(&game->player.pos, new_pos, PLAYER_RADIUS, game);
}

void	handle_yaw(t_game *game, float speed, float old_dir_x,
	float old_plane_x)
{
	if (game->state[S_ROT_L] && game->state[S_ROT_R])
		return ;
	if (game->state[S_ROT_L])
	{
		game->player.dir.x = game->player.dir.x * cos(-speed)
			- game->player.dir.y * sin(-speed);
		game->player.dir.y = old_dir_x * sin(-speed)
			+ game->player.dir.y * cos(-speed);
		game->player.plane.x = game->player.plane.x
			* cos(-speed) - game->player.plane.y * sin(-speed);
		game->player.plane.y = old_plane_x * sin(-speed)
			+ game->player.plane.y * cos(-speed);
	}
	else if (game->state[S_ROT_R])
	{
		game->player.dir.x = game->player.dir.x * cos(speed)
			- game->player.dir.y * sin(speed);
		game->player.dir.y = old_dir_x * sin(speed)
			+ game->player.dir.y * cos(speed);
		game->player.plane.x = game->player.plane.x * cos(speed)
			- game->player.plane.y * sin(speed);
		game->player.plane.y = old_plane_x * sin(speed)
			+ game->player.plane.y * cos(speed);
	}
}

void	handle_pitch(t_game *game)
{
	const int	limit = RES_Y2;

	if (game->state[S_ROT_U] && game->state[S_ROT_D])
		return ;
	if (game->state[S_ROT_U])
		game->player.pitch -= game->frame.time;
	else if (game->state[S_ROT_D])
		game->player.pitch += game->frame.time;
	if (game->player.pitch < -limit)
		game->player.pitch = -limit;
	else if (game->player.pitch > limit)
		game->player.pitch = limit;
}

void	handle_movement(t_game *game)
{
	int	run_speed;

	if (game->state[S_CAUGHT])
		return ;
	run_speed = 1;
	if (game->state[S_RUN] == 1 && !game->pwl.item.collected)
	{
		game->state[S_MAP_BIG] = 0;
		run_speed = RUN_SPD;
	}
	handle_movement_xy(game, PLAYER_SPD * game->frame.time * run_speed);
	handle_pitch(game);
	handle_yaw(game, ROT_SPD * game->frame.time,
		game->player.dir.x, game->player.plane.x);
}

int	delay_ms(unsigned int ms, struct timeval *timer)
{
	struct timeval			current_time;
	long					ms_elapsed;

	if (timer->tv_sec == 0 && timer->tv_usec == 0)
	{
		gettimeofday(timer, NULL);
		return (0);
	}
	gettimeofday(&current_time, NULL);
	ms_elapsed = (current_time.tv_sec - timer->tv_sec) * 1000;
	ms_elapsed += (current_time.tv_usec - timer->tv_usec) / 1000;
	if (ms_elapsed >= ms)
	{
		*timer = current_time;
		return (1);
	}
	return (0);
}

int	should_render_frame(t_game *game)
{
	long		elapsed;

	gettimeofday(&game->frame.current, NULL);
	elapsed = (game->frame.current.tv_sec - game->frame.last.tv_sec) * 1000
		+ (game->frame.current.tv_usec - game->frame.last.tv_usec) * 0.001;
	if (elapsed >= game->frame.time)
	{
		game->frame.fps++;
		game->frame.last = game->frame.current;
		if (delay_ms(1000, &game->timer[MS1000]))
		{
			ft_free(&game->frame.fps_str);
			game->frame.fps_str = ft_itoa(game->frame.fps);
			game->frame.fps = 0;
		}
		return (1);
	}
	return (0);
}

void	draw_map_enemy(t_game *game)
{
	t_point		start;
	t_point		end;

	start.x = (int)(game->enemy.pos.x * MAP_CELL_SIZE);
	start.y = (int)(game->enemy.pos.y * MAP_CELL_SIZE);
	end.x = (int)(game->enemy.last_seen.x * MAP_CELL_SIZE);
	end.y = (int)(game->enemy.last_seen.y * MAP_CELL_SIZE);
	if (delay_ms(200, &game->timer[TIMER_ENEMY_PATH]))
		draw_circle(&game->img[T_MAP_ENEMY_PATH], start, 1, WHITE);
	if (game->state[S_ENEMY_PATH])
		put_img((t_point){0, 0},
			&game->img[T_MAP_ENEMY_PATH], &game->img[T_MAP]);
	if (game->enemy.last_seen.x && game->enemy.last_seen.y)
	{
		draw_line(&game->img[T_MAP], start, end, RED);
		draw_circle(&game->img[T_MAP], end, MAP_CELL_SIZE * 0.15, RED);
		draw_circle_outline(&game->img[T_MAP], end, MAP_CELL_SIZE * 0.25, RED);
	}
	if (game->state[S_ENEMY_ICON])
	{
		draw_circle(&game->img[T_MAP], start,
			MAP_CELL_SIZE * 0.5, MAP_COLOR);
		draw_circle_outline(&game->img[T_MAP], start,
			MAP_CELL_SIZE * 0.5, BLACK);
	}
}

void	draw_minimap(t_game *game)
{
	t_fpoint	player_pos;
	const int	center = game->img[T_MAP_MASK].size.x * 0.5;

	if (game->state[S_MAP_DISABLE])
		return ;
	player_pos.x = (int)((game->player.pos.x * MAP_CELL_SIZE));
	player_pos.y = (int)((game->player.pos.y * MAP_CELL_SIZE));
	if (game->map.update)
		update_map_tiles(game);
	put_img((t_point){0, 0}, &game->img[T_MAP_TILES], &game->img[T_MAP]);
	if (!game->state[S_ENEMY_DEAD])
		draw_map_enemy(game);
	draw_map_player(&game->img[T_MAP], game->player);
	put_img((t_point){0, 0,}, &game->img[T_MAP_BG], &game->img[T_MAP_MASK]);
	put_img((t_point){-player_pos.x + center, -player_pos.y + center},
		&game->img[T_MAP], &game->img[T_MAP_MASK]);
	if (!game->state[S_MAP_BIG])
		put_img(game->map.offset, &game->img[T_MAP_MASK], &game->img[T_WIN]);
	else
		put_img((t_point){RES_X2 - game->img[T_MAP].size.x * 0.5,
			RES_Y * 0.5 - game->img[T_MAP].size.y * 0.5},
			&game->img[T_MAP], &game->img[T_WIN]);
}

float	set_intensity(t_light light, float dist)
{
	const float	inverse_range = 1.0 / (light.max - light.min);
	float		intensity;

	intensity = (light.max - dist) * inverse_range;
	if (intensity < 0)
		intensity = 0;
	if (intensity > 1)
		intensity = 1;
	intensity = intensity * (1 - light.ambient) + light.ambient;
	return (intensity);
}

void	assign_wall_textures(t_game *game, t_ray *r, t_texture_map *tex)
{
	if (r->side == VERTICAL)
	{
		tex->wall_tex = &game->img[T_EAST];
		if (r->dir.x <= 0)
		{
			tex->wall_tex = &game->img[T_WEST];
			tex->coords.x = WALL - tex->coords.x - 1;
		}
	}
	else if (r->side == HORIZONTAL)
	{
		tex->wall_tex = &game->img[T_NORTH];
		if (r->dir.y >= 0)
		{
			tex->wall_tex = &game->img[T_SOUTH];
			tex->coords.x = WALL - tex->coords.x - 1;
		}
	}
}

// Sets the img pointer in texture struct,
// based on the value in the array that the ray has hit.
void	assign_tile_textures(t_game *game, t_ray *r, t_texture_map *tex)
{
	tex->wall_tex = NULL;
	if (game->map.arr[(int)r->map.y][(int)r->map.x] < 1
		|| game->map.arr[(int)r->map.y][(int)r->map.x] == TILE_PWL)
		return ;
	if (game->map.arr[(int)r->map.y][(int)r->map.x] == 2)
	{
		if ((r->side == VERTICAL && r->dir.x <= 0)
			|| (r->side == HORIZONTAL && r->dir.y >= 0))
			tex->coords.x = WALL - tex->coords.x - 1;
		tex->wall_tex = &game->img[T_DOOR_CLOSE];
		return ;
	}
	assign_wall_textures(game, r, tex);
}

// Shoots a ray until it has hit a value in the array larger than 0.
int	dda(t_ray *r, t_game *game)
{
	while (1)
	{
		set_dda_step_side(r);
		if (out_of_bounds(r->map, game))
			return (-1);
		if (game->map.arr[(int)r->map.y][(int)r->map.x] > 0
			&& game->map.arr[(int)r->map.y][(int)r->map.x] != TILE_PWL)
			return (0);
	}
}

// Draws vertical slices of the wall projections, from left to right.
void	draw_wall_slices(t_game *game, t_ray *r, t_texture_map *tex)
{
	tex->wall_tex->intensity
		= set_intensity(game->light, r->wall_dist * game->player.zoom);
	tex->tex_step = 1.0 * WALL / r->line_height;
	r->pix.y = r->draw_start;
	tex->hit.y = (r->draw_start + game->player.pitch
			- (r->line_height * game->player.z)
			- (RES_Y - r->line_height) * 0.5) * tex->tex_step;
	while (r->pix.y < r->draw_end)
	{
		tex->coords.y = (int)tex->hit.y & (WALL - 1);
		tex->hit.y += tex->tex_step;
		set_pixel_alpha(&game->img[T_WIN], r->pix.x, r->pix.y,
			darken(get_pixel(tex->wall_tex, tex->coords.x, tex->coords.y),
				tex->wall_tex->intensity));
		r->pix.y++;
	}
}

// Determine the height of a vertical slice, based on how far a ray traversed.
void	calculate_wall_projection(t_game *game, t_ray *r, t_texture_map *tex)
{
	if (r->side == VERTICAL)
		r->wall_dist = r->side_dist.x - r->delta_dist.x;
	else
		r->wall_dist = r->side_dist.y - r->delta_dist.y;
	r->line_height = (int)(RES_Y / r->wall_dist);
	r->draw_start = (RES_Y - r->line_height) * 0.5 - game->player.pitch
		+ (r->line_height * game->player.z);
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = (r->line_height + RES_Y) * 0.5 - game->player.pitch
		+ (r->line_height * game->player.z);
	if (r->draw_end >= RES_Y)
		r->draw_end = RES_Y;
	if (r->side == VERTICAL)
		tex->hit.x = game->player.pos.y + r->wall_dist * r->dir.y;
	else
		tex->hit.x = game->player.pos.x + r->wall_dist * r->dir.x;
	tex->hit.x -= floorf(tex->hit.x);
	tex->coords.x = (int)(tex->hit.x * WALL);
}

void	draw_bg(t_game *game)
{
	put_img((t_point){0, 0}, &game->img[T_CEILING], &game->img[T_WIN]);
	put_img((t_point){0, RES_Y2 - game->player.pitch},
		&game->img[T_FLOOR], &game->img[T_WIN]);
	put_img_scale((t_point){0, RES_Y2 - game->player.pitch},
		&game->img[T_DITHER], &game->img[T_WIN],
		(t_fpoint){1, (1 - (P_MAX_HEIGHT - game->player.z)
			/ (0.5 + P_MAX_HEIGHT)) * game->player.zoom});
}

void	render_walls(t_game *game)
{
	t_texture_map	tex;
	t_ray			r;
	const float		camera_x_factor = 2.0 / RES_X;

	draw_bg(game);
	if (out_of_bounds(game->player.pos, game))
		return ;
	r.pix.x = 0;
	while (r.pix.x < RES_X)
	{
		set_ray_direction(game, &r, r.pix.x * camera_x_factor - 1, 1);
		set_ray_step_direction(game, &r);
		if (dda(&r, game) == -1)
			return ;
		calculate_wall_projection(game, &r, &tex);
		assign_tile_textures(game, &r, &tex);
		draw_wall_slices(game, &r, &tex);
		r.pix.x++;
	}
}

void	display_fps_counter(t_game *game)
{
	if (game->frame.fps_str)
	{
		mlx_string_put(game->mlx, game->win, 4, 13, WHITE,
			game->frame.fps_str);
		mlx_string_put(game->mlx, game->win, 20, 13, WHITE,
			"FPS");
	}
	else
		mlx_string_put(game->mlx, game->win, 4, 13, WHITE,
			"INITIALIZING FPS...");
}

int	d100(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_usec + 42) ^ 42) % 100);
}

void	set_player_look_at(t_player *player, t_fpoint enemy_pos)
{
	t_fpoint	new_dir;
	float		magnitude;
	const float	smoothness = 0.5;

	new_dir.x = enemy_pos.x - player->pos.x;
	new_dir.y = enemy_pos.y - player->pos.y;
	magnitude = sqrtf(new_dir.x * new_dir.x + new_dir.y * new_dir.y);
	if (magnitude != 0)
	{
		new_dir.x /= magnitude;
		new_dir.y /= magnitude;
	}
	player->dir.x += (new_dir.x - player->dir.x) * smoothness;
	player->dir.y += (new_dir.y - player->dir.y) * smoothness;
	player->plane.x = -player->dir.y * 0.66;
	player->plane.y = player->dir.x * 0.66;
}

void	enemy_open_door(t_game *game)
{
	if (game->map.arr[(int)game->enemy.pos.y][(int)game->enemy.pos.x] == 2)
		game->map.arr[(int)game->enemy.pos.y][(int)game->enemy.pos.x] = -2;
	if (game->map.arr[(int)game->enemy.pos.y - 1][(int)game->enemy.pos.x] == 2)
		game->map.arr[(int)game->enemy.pos.y - 1][(int)game->enemy.pos.x] = -2;
	if (game->map.arr[(int)game->enemy.pos.y + 1][(int)game->enemy.pos.x] == 2)
		game->map.arr[(int)game->enemy.pos.y + 1][(int)game->enemy.pos.x] = -2;
	if (game->map.arr[(int)game->enemy.pos.y][(int)game->enemy.pos.x - 1] == 2)
		game->map.arr[(int)game->enemy.pos.y][(int)game->enemy.pos.x - 1] = -2;
	if (game->map.arr[(int)game->enemy.pos.y][(int)game->enemy.pos.x + 1] == 2)
		game->map.arr[(int)game->enemy.pos.y][(int)game->enemy.pos.x + 1] = -2;
	game->map.update = 1;
}

void	move_enemy_cardinal(t_game *game, int direction, t_fpoint *new_pos)
{
	t_point		step_dir;

	step_dir.x = 0;
	step_dir.y = 0;
	if (direction == S_UP)
		step_dir.y = -1;
	else if (direction == S_DOWN)
		step_dir.y = 1;
	else if (direction == S_LEFT)
		step_dir.x = -1;
	else if (direction == S_RIGHT)
		step_dir.x = 1;
	new_pos->x = game->enemy.pos.x + step_dir.x * ENEMY_SPD * game->frame.time;
	new_pos->y = game->enemy.pos.y + step_dir.y * ENEMY_SPD * game->frame.time;
}

void	move_enemy_diagonal(t_game *game, int direction, t_fpoint *new_pos)
{
	t_point		step_dir;

	step_dir.x = 0;
	step_dir.y = 0;
	if (direction == UP_LEFT || direction == UP_RIGHT)
	{
		step_dir.x = -1;
		step_dir.y = -1;
		if (direction == UP_RIGHT)
			step_dir.x = 1;
	}
	else if (direction == DOWN_LEFT || direction == DOWN_RIGHT)
	{
		step_dir.x = -1;
		step_dir.y = 1;
		if (direction == DOWN_RIGHT)
			step_dir.x = 1;
	}
	new_pos->x = game->enemy.pos.x + step_dir.x * ENEMY_SPD * game->frame.time;
	new_pos->y = game->enemy.pos.y + step_dir.y * ENEMY_SPD * game->frame.time;
}

void	move_enemy(t_game *game, t_fpoint *new_pos)
{
	if (game->enemy.move_seed >= 0 && game->enemy.move_seed <= 12)
		move_enemy_cardinal(game, S_UP, new_pos);
	else if (game->enemy.move_seed >= 13 && game->enemy.move_seed <= 25)
		move_enemy_cardinal(game, S_DOWN, new_pos);
	else if (game->enemy.move_seed >= 26 && game->enemy.move_seed <= 38)
		move_enemy_cardinal(game, S_LEFT, new_pos);
	else if (game->enemy.move_seed >= 39 && game->enemy.move_seed <= 51)
		move_enemy_cardinal(game, S_RIGHT, new_pos);
	else if (game->enemy.move_seed >= 52 && game->enemy.move_seed <= 63)
		move_enemy_diagonal(game, UP_LEFT, new_pos);
	else if (game->enemy.move_seed >= 64 && game->enemy.move_seed <= 75)
		move_enemy_diagonal(game, UP_RIGHT, new_pos);
	else if (game->enemy.move_seed >= 76 && game->enemy.move_seed <= 87)
		move_enemy_diagonal(game, DOWN_LEFT, new_pos);
	else
		move_enemy_diagonal(game, DOWN_RIGHT, new_pos);
}

void	hunt(t_game *game)
{
	t_fpoint	new_pos;

	if (game->enemy.move_seed == 0)
		game->enemy.move_seed = d100();
	else
	{
		if (delay_ms(game->enemy.move_inc, &game->timer[TIMER_ENEMY]))
		{
			game->enemy.move_inc += 1000;
			game->enemy.move_seed = d100();
		}
	}
	move_enemy(game, &new_pos);
	if (check_collision(&game->enemy.pos, new_pos, ENEMY_RADIUS, game))
	{
		game->enemy.move_seed = 0;
		game->enemy.move_inc = 0;
	}
	if (d100() == 1)
		enemy_open_door(game);
}

void	game_over(t_game *game)
{
	if (game->pwl.item.collected)
		return ;
	if (!game->state[S_CAUGHT])
		write(1, "\a", 1);
	game->state[S_MAP_DISABLE] = 1;
	set_player_look_at(&game->player, game->enemy.pos);
	if (game->player.zoom < 1.8)
		game->player.zoom += 0.1;
	game->player.pitch = -300;
	game->state[S_CAUGHT] = 1;
}

void	chase(t_game *game, float dist_sq, float speed)
{
	if (game->state[S_ENEMY_VISION] == 1)
	{
		game->enemy.last_seen.x = game->player.pos.x;
		game->enemy.last_seen.y = game->player.pos.y;
		game->enemy.last_dist.x = game->enemy.dist.x;
		game->enemy.last_dist.y = game->enemy.dist.y;
	}
	game->enemy.memory.x = game->enemy.pos.x + game->enemy.last_dist.x * speed;
	game->enemy.memory.y = game->enemy.pos.y + game->enemy.last_dist.y * speed;
	if (dist_sq < 1.415)
		return (game_over(game));
	enemy_open_door(game);
	if (((int)game->enemy.pos.x == (int)game->enemy.last_seen.x
			&& (int)game->enemy.pos.y == (int)game->enemy.last_seen.y)
		|| check_collision(&game->enemy.pos,
			game->enemy.memory, ENEMY_RADIUS, game))
	{
		game->enemy.last_seen.x = 0;
		game->enemy.last_seen.y = 0;
		game->enemy.memory.x = 0;
		game->enemy.memory.y = 0;
	}
}

void	update_enemy_pos(t_game *game)
{
	float		dist_sq;
	float		normalized_speed;

	if (game->state[S_ENEMY_DEAD])
		return ;
	if (game->state[S_ENEMY_VISION] == 0
		&& (game->enemy.memory.x == 0 && game->enemy.memory.y == 0))
		return (hunt(game));
	game->enemy.dist.x = game->player.pos.x - game->enemy.pos.x;
	game->enemy.dist.y = game->player.pos.y - game->enemy.pos.y;
	dist_sq = game->enemy.dist.x * game->enemy.dist.x
		+ game->enemy.dist.y * game->enemy.dist.y;
	normalized_speed = (ENEMY_SPD * game->frame.time) / sqrtf(dist_sq);
	if (game->pwl.item.collected)
		normalized_speed = -normalized_speed;
	chase(game, dist_sq, normalized_speed);
}

void	init_ray_to_target(t_game *game, t_ray *r, t_fpoint target_pos)
{
	float	magnitude;

	r->dir.x = target_pos.x - game->player.pos.x;
	r->dir.y = target_pos.y - game->player.pos.y;
	magnitude = sqrtf(r->dir.x * r->dir.x + r->dir.y * r->dir.y);
	r->dir.x /= magnitude;
	r->dir.y /= magnitude;
	r->map.x = (int)game->player.pos.x;
	r->map.y = (int)game->player.pos.y;
	r->delta_dist.x = fabsf(1 / r->dir.x);
	r->delta_dist.y = fabsf(1 / r->dir.y);
	set_ray_step_direction(game, r);
}

int	dda_to_target(t_game *game, t_ray *r, t_fpoint target_pos)
{
	if ((int)target_pos.x == (int)game->player.pos.x
		&& (int)target_pos.y == (int)game->player.pos.y)
		return (1);
	while (1)
	{
		set_dda_step_side(r);
		if (out_of_bounds(r->map, game)
			|| (game->map.arr[(int)r->map.y][(int)r->map.x] > 0
			&& game->map.arr[(int)r->map.y][(int)r->map.x] != TILE_PWL))
			return (0);
		if ((int)r->map.x == (int)target_pos.x
			&& (int)r->map.y == (int)target_pos.y)
			return (1);
	}
}

void	update_enemy_sprite(t_game *game)
{
	game->enemy.img = game->img[game->enemy.frame];
	if (!game->pwl.item.collected)
	{
		game->enemy.frame++;
		if (game->enemy.frame == T_XENO7 + 1)
			game->enemy.frame = T_XENO0;
		return ;
	}
	game->enemy.frame--;
	if (game->enemy.frame == T_XENO0 -1)
		game->enemy.frame = T_XENO7;
}

float	dot_product(t_fpoint a, t_fpoint b)
{
	return (a.x * b.x + a.y * b.y);
}

void	render_enemy(t_game *game)
{
	t_fpoint	view;
	t_fpoint	screen;
	t_fpoint	scale;
	float		dist_sqrt;
	float		scaling;

	game->state[S_ENEMY_VISION] = 1;
	view.x = dot_product(game->player.dir, game->enemy.dist) * 0.9;
	if (view.x >= 0)
		return ;
	dist_sqrt = sqrtf(game->enemy.dist.x * game->enemy.dist.x
			+ game->enemy.dist.y * game->enemy.dist.y);
	view.y = dot_product(game->player.plane, game->enemy.dist);
	screen.x = (RES_X * (view.y * 2.0) / (2 * view.x)) * game->player.zoom;
	screen.y = ((RES_Y * game->player.z) / dist_sqrt - game->player.pitch);
	scaling = fmaxf((game->img[T_XENO0].size.x / dist_sqrt)
			* game->player.zoom * 0.1, 0.1);
	scale.x = scaling;
	scale.y = scaling;
	if (view.x < 0)
		put_img_scale_mid((t_point){screen.x, screen.y},
			&game->enemy.img, &game->img[T_WIN], scale);
}

void	render_enemy_sprite(t_game *game)
{
	t_ray	r;

	if (game->state[S_ENEMY_DEAD])
		return ;
	if (delay_ms(75, &game->timer[MS100]))
	{
		game->state[S_ENEMY_ICON] = !game->state[S_ENEMY_ICON];
		update_enemy_sprite(game);
	}
	init_ray_to_target(game, &r, game->enemy.pos);
	if (dda_to_target(game, &r, game->enemy.pos) != 1)
	{
		game->state[S_ENEMY_VISION] = 0;
		return ;
	}
	render_enemy(game);
}

void	render_item_sprite(t_game *game, t_coin item)
{
	t_fpoint	view;
	t_fpoint	screen;
	t_fpoint	scale;
	float		dist_sqrt;
	float		scaling;

	dist_sqrt = sqrtf(item.dist.x * item.dist.x + item.dist.y * item.dist.y);
	if (dist_sqrt > 3)
		return ;
	view.x = dot_product(game->player.dir, item.dist) * 0.88;
	if (view.x >= 0)
		return ;
	view.y = dot_product(game->player.plane, item.dist);
	screen.x = (RES_X * (view.y * 2.0) / (2 * view.x)) * game->player.zoom;
	screen.y = (float)-game->player.pitch;
	scaling = fmaxf((game->img[T_ITEM].size.x / dist_sqrt)
			* game->player.zoom * 0.04, 0.04);
	scale.x = scaling;
	scale.y = scaling;
	if (screen.x < -RES_X2 - 32 * scaling || screen.x > RES_X2 + 32 * scaling
		|| (screen.y + game->img[T_ITEM].size.y * scaling) > 382)
		return ;
	put_img_scale_mid_bot((t_point){screen.x, screen.y},
		&game->img[T_ITEM], &game->img[T_WIN], scale);
}

void	render_item(t_game *game)
{
	t_ray	r;
	int		i;

	i = 0;
	while (i < game->item.count)
	{
		if (game->item.arr[i].collected == 1)
		{
			i++;
			continue ;
		}
		init_ray_to_target(game, &r, game->item.arr[i].pos);
		if (dda_to_target(game, &r, game->item.arr[i].pos) != 1)
		{
			i++;
			continue ;
		}
		game->item.arr[i].dist.x = game->player.pos.x - game->item.arr[i].pos.x;
		game->item.arr[i].dist.y = game->player.pos.y - game->item.arr[i].pos.y;
		render_item_sprite(game, game->item.arr[i]);
		i++;
	}
}

int	same_position(t_fpoint p1, t_fpoint p2)
{
	if ((int)p1.x == (int)p2.x && (int)p1.y == (int)p2.y)
		return (1);
	return (0);
}

void	pickup_item(t_game *game)
{
	int	i;

	if (game->map.arr[(int)game->player.pos.y][(int)game->player.pos.x]
		== TILE_ITEM)
	{
		i = 0;
		while (i < game->item.count)
		{
			if (same_position(game->player.pos, game->item.arr[i].pos))
			{
				game->item.collected++;
				game->item.arr[i].collected = 1;
				game->map.arr[(int)game->player.pos.y][(int)game->player.pos.x]
					= 0;
				game->map.update = 1;
				return ;
			}
			i++;
		}
	}
}

void	set_pwl_view(t_game *game, t_ray r)
{
	if (r.dir.x > 0.5 && r.dir.y < -0.5)
		game->pwl.item_img = game->img[T_PWL0];
	else if (r.dir.x > 0.5 && r.dir.y > 0.5)
		game->pwl.item_img = game->img[T_PWL2];
	else if (r.dir.x < -0.5 && r.dir.y > 0.5)
		game->pwl.item_img = game->img[T_PWL4];
	else if (r.dir.x < -0.5 && r.dir.y < -0.5)
		game->pwl.item_img = game->img[T_PWL6];
	else if (r.dir.x > 0.5)
		game->pwl.item_img = game->img[T_PWL1];
	else if (r.dir.y > 0.5)
		game->pwl.item_img = game->img[T_PWL3];
	else if (r.dir.x < -0.5)
		game->pwl.item_img = game->img[T_PWL5];
	else if (r.dir.y < -0.5)
		game->pwl.item_img = game->img[T_PWL7];
}

void	render_pwl_sprite(t_game *game, t_ray r)
{
	t_fpoint	view;
	t_fpoint	screen;
	t_fpoint	scale;
	float		dist_sq;
	float		scaling;

	game->pwl.item.dist.x = game->player.pos.x - game->pwl.item.pos.x;
	game->pwl.item.dist.y = game->player.pos.y - game->pwl.item.pos.y;
	view.x = dot_product(game->player.dir, game->pwl.item.dist) * 0.88;
	if (view.x >= 0)
		return ;
	dist_sq = sqrtf(game->pwl.item.dist.x * game->pwl.item.dist.x
			+ game->pwl.item.dist.y * game->pwl.item.dist.y);
	view.y = dot_product(game->player.plane, game->pwl.item.dist);
	screen.x = (RES_X * (view.y * 2.0) / (2 * view.x)) * game->player.zoom;
	screen.y = ((RES_Y * game->player.z) / dist_sq - game->player.pitch);
	scaling = fmaxf((game->img[T_ITEM].size.x / dist_sq)
			* game->player.zoom * 0.1, 0.1);
	scale.x = scaling;
	scale.y = scaling;
	set_pwl_view(game, r);
	game->pwl.item_img.intensity = set_intensity(game->light, dist_sq);
	put_img_scale_darken((t_point){screen.x, screen.y},
		&game->pwl.item_img, &game->img[T_WIN], scale);
}

void	enemy_hit_check(t_game *game)
{
	t_ray	r;
	float	dist_sq;

	dist_sq = game->enemy.dist.x * game->enemy.dist.x
		+ game->enemy.dist.y * game->enemy.dist.y;
	set_ray_direction(game, &r, 0, 0);
	set_ray_step_direction(game, &r);
	if (dda_to_target(game, &r, game->enemy.pos) && dist_sq < 4)
		game->state[S_ENEMY_DEAD] = 1;
}

void	render_pwl_overlay(t_game *game)
{
	if (game->state[S_PUNCHING] == 1)
	{
		if (delay_ms(100, &game->timer[TIMER_PWL]))
		{
			game->pwl.frame++;
			game->pwl.overlay_img = game->img[game->pwl.frame];
			if (game->pwl.frame == T_PWL_ARM6 + 1)
			{
				game->pwl.frame = T_PWL_ARM0;
				game->pwl.overlay_img = game->img[T_PWL_ARM0];
				game->state[S_PUNCHING] = 0;
			}
		}
		if (game->pwl.frame == T_PWL_ARM4)
			enemy_hit_check(game);
	}
	if (game->player.zoom == 1)
		return (put_img((t_point){0, 136},
			&game->pwl.overlay_img, &game->img[T_WIN]));
	put_img_scale_mid((t_point){0, 68}, &game->pwl.overlay_img,
		&game->img[T_WIN], (t_fpoint){game->player.zoom, game->player.zoom});
}

void	render_pwl(t_game *game)
{
	t_ray	r;

	if (game->pwl.item.collected == 1)
		return (render_pwl_overlay(game));
	init_ray_to_target(game, &r, game->pwl.item.pos);
	if (dda_to_target(game, &r, game->pwl.item.pos) != 1)
		return ;
	render_pwl_sprite(game, r);
}

void	display_msg(t_game *game)
{
	if (game->state[S_ENEMY_DEAD])
	{
		mlx_string_put(game->mlx, game->win, 4, 26, WHITE,
			"CONGRATULATIONS! [ESC] to quit");
		return ;
	}
	if (game->state[S_CAUGHT])
	{
		mlx_string_put(game->mlx, game->win, 4, 26, WHITE,
			"YOU DIED! [ESC] to quit");
		return ;
	}
	if (game->state[S_MOUSE] == 0)
		mlx_string_put(game->mlx, game->win, 4, 26, WHITE,
			"MOUSE DISABLED, [CLICK ANYWHERE] to enable");
	else
		mlx_string_put(game->mlx, game->win, 4, 26, WHITE,
			"MOUSE ENABLED, [P] to disable");
	if (game->pwl.item.collected)
		mlx_string_put(game->mlx, game->win, 4, 39, WHITE,
			"[SPACE] or [CLICK] to punch");
	else
		mlx_string_put(game->mlx, game->win, 4, 39, WHITE,
			"[WSAD] or [ARROW KEYS] to move, [SHIFT] to run");
}

int	display_pause_screen(t_game *game)
{
	if (!game->state[S_PAUSE])
		return (0);
	put_img((t_point){0, 0}, &game->img[T_PAUSE], &game->img[T_WIN]);
	mlx_put_image_to_window(game->mlx, game->win, game->img[T_WIN].img, 0, 0);
	return (1);
}

int	game_loop(t_game *game)
{
	if (game->state[S_MOUSE] && !game->state[S_PAUSE] && !game->state[S_CAUGHT])
		handle_mouselook(game);
	if (should_render_frame(game))
	{
		if (display_pause_screen(game))
			return (0);
		update_enemy_pos(game);
		handle_movement(game);
		render_walls(game);
		render_enemy_sprite(game);
		pickup_item(game);
		render_item(game);
		render_pwl(game);
		draw_minimap(game);
		mlx_put_image_to_window(game->mlx, game->win,
			game->img[T_WIN].img, 0, 0);
		interact(game);
		display_fps_counter(game);
		display_msg(game);
	}
	return (0);
}

void	init_player(t_player *player, t_point starting_pos)
{
	player->pos.x = starting_pos.x + 0.5;
	player->pos.y = starting_pos.y + 0.5;
	player->dir.x = 0;
	player->dir.y = -1;
	player->plane.x = -player->dir.y * 0.66;
	player->plane.y = player->dir.x * 0.66;
	player->zoom = 1.0;
}

void	init_framedata(t_frame_data *frame)
{
	frame->fps_target = 30;
	frame->time = 1000.0 / frame->fps_target;
	gettimeofday(&frame->last, NULL);
}

void	init_enemy(t_game *game)
{
	game->enemy.pos.x = game->scene.pos_xeno.x + 0.5;
	game->enemy.pos.y = game->scene.pos_xeno.y + 0.5;
	game->enemy.frame = T_XENO0;
	game->enemy.img = game->img[T_XENO0];
}

int	count_tile(t_game *game, int n)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (y < game->map.size.y - 1)
	{
		x = 0;
		while (x < game->map.size.x - 1)
		{
			if (game->map.arr[y][x] == n)
				count++;
			x++;
		}
		y++;
	}
	(void)game;
	return (count);
}

void	init_items(t_game *game)
{
	int	x;
	int	y;
	int	i;

	game->item.count = count_tile(game, -3);
	game->item.arr = ft_calloc(game->item.count, sizeof(t_coin));
	i = 0;
	y = 0;
	while (y < game->map.size.y - 1)
	{
		x = 0;
		while (x < game->map.size.x - 1)
		{
			if (game->map.arr[y][x] == -3)
			{
				game->item.arr[i].pos.x = (float)x + 0.5;
				game->item.arr[i].pos.y = (float)y + 0.5;
				i++;
				if (i == game->item.count)
					return ;
			}
			x++;
		}
		y++;
	}
}

t_fpoint	get_unique_char_pos(t_game *game, int n)
{
	t_fpoint	pos;

	pos.y = 0;
	while (pos.y < game->map.size.y - 1)
	{
		pos.x = 0;
		while (pos.x < game->map.size.x - 1)
		{
			if (game->map.arr[(int)pos.y][(int)pos.x] == n)
			{
				pos.x += 0.5;
				pos.y += 0.5;
				return (pos);
			}
			pos.x++;
		}
		pos.y++;
	}
	(void)game;
	return ((t_fpoint){0, 0});
}

void	init_pwl(t_game *game)
{
	game->pwl.item.pos.x = game->scene.pos_powerloader.x + 0.5;
	game->pwl.item.pos.y = game->scene.pos_powerloader.y + 0.5;
	game->pwl.overlay_img = game->img[T_PWL_ARM0];
	game->pwl.frame = T_PWL_ARM0;
}

int	init_game(t_game *game, t_scene scene)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return (1);
	mlx_do_key_autorepeatoff(game->mlx);
	game->win = mlx_new_window(game->mlx, RES_X, RES_Y, "cub3D");
	if (game->win == NULL)
		return (1);
	if (init_img(game->mlx, &game->img[T_WIN], RES_X, RES_Y) == -1)
		return (2);
	if (init_minimap(game, scene.map_dim) == -1
		|| init_bg(game, scene.hex_ceiling, scene.hex_floor) == -1)
		return (2);
	if (load_xpms(game))
		return (3);
	init_framedata(&game->frame);
	init_player(&game->player, scene.pos_player);
	init_enemy(game);
	init_items(game);
	init_pwl(game);
	game->light.min = 0.25;
	game->light.max = 2.5;
	game->light.ambient = 0.15;
	mlx_mouse_move(game->mlx, game->win, RES_X2, RES_Y2);
	return (0);
}

int	mwheel(unsigned int key, t_game *game)
{
	const float	step = 0.1;
	const int	limit = RES_Y2;

	if (key == 4 && game->player.zoom < 1.8)
	{
		game->player.zoom += step;
		if (game->player.pitch != limit && game->player.pitch != -limit)
			game->player.pitch *= game->player.zoom
				/ (game->player.zoom - step);
	}
	else if (key == 5 && game->player.zoom > 1)
	{
		game->player.zoom -= step;
		if (game->player.pitch != limit && game->player.pitch != -limit)
			game->player.pitch *= game->player.zoom
				/ (game->player.zoom + step);
		if (game->player.pitch > limit)
			game->player.pitch = limit;
		else if (game->player.pitch < -limit)
			game->player.pitch = -limit;
	}
	return (0);
}

int	mouse_event(unsigned int key, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (game->state[S_CAUGHT])
		return (0);
	if (key == 1)
	{
		if (game->state[S_MOUSE] == 0)
		{
			mlx_mouse_move(game->mlx, game->win, RES_X2, RES_Y2);
			game->state[S_MOUSE] = 1;
		}
		if (game->pwl.item.collected && game->state[S_MOUSE])
			game->state[S_PUNCHING] = 1;
	}
	return (mwheel(key, game));
}

void	error_handler(t_game *game, int status)
{
	if (status == 1)
		cleanup(game, 1, "cub3D: Error: Failed to initialize game\n");
	else if (status == 2)
		cleanup(game, 1, "cub3D: Error: Failed to create image\n");
	else if (status == 3)
		cleanup(game, 1, "cub3D: Error: Missing texture file/files\n");
}

int	main(int ac, char **av)
{
	int		status;
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (validate_input(ac, av, &game.scene) == -1)
		return (1);
	status = init_game(&game, game.scene);
	free_scene_struct(&game.scene);
	if (status)
		error_handler(&game, status);
	mlx_do_key_autorepeatoff(game.mlx);
	mlx_hook(game.win, KeyPress, KeyPressMask, &key_press, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, &key_release, &game);
	mlx_hook(game.win, ButtonPress, ButtonPressMask, &mouse_event, &game);
	mlx_hook(game.win, DestroyNotify, DestroyAll, &exit_game, &game);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
