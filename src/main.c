/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:44:00 by jaslim            #+#    #+#             */
/*   Updated: 2024/09/13 03:39:56 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	g_map_x = 24;
int	g_map_y = 24;
int	g_map[24][24] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

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

void	set_pixel(t_img *img, int x, int y, unsigned int color)
{
	char			*dst;

	if (x < 0 || y < 0 || x >= img->size.x || y >= img->size.y || (color >> 24) & 0xFF)
		return ;
	dst = img->addr + ((y * img->line_len) + (x * (img->bits_per_pixel / 8)));
	*(unsigned int *)dst = color;
}

unsigned int	get_pixel(t_img *img, int x, int y)
{
	char	*src;

	src = img->addr + ((y * img->line_len) + (x * (img->bits_per_pixel / 8)));
	return (*(unsigned int *)src);
}

void	put_img_scale(t_point offset, t_img *src, t_img *dst, t_fpoint scale)
{
	t_fpoint	src_pos;
	t_point		dst_pos;

	dst_pos.y = 0;
	while (dst_pos.y < dst->size.y)
	{
		dst_pos.x = 0;
		while (dst_pos.x < dst->size.x)
		{
			src_pos.x = (dst_pos.x - offset.x) / scale.x;
			src_pos.y = (dst_pos.y - offset.y) / scale.y;
			if (src_pos.x >= 0 && src_pos.x < src->size.x &&
				src_pos.y >= 0 && src_pos.y < src->size.y)
				set_pixel(dst, dst_pos.x, dst_pos.y,
					get_pixel(src, src_pos.x, src_pos.y));
			dst_pos.x++;
		}
		dst_pos.y++;
	}
}

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
				set_pixel(dst, dst_pos.x, dst_pos.y,
					get_pixel(src, src_pos.x, src_pos.y));
			src_pos.x++;
		}
		src_pos.y++;
	}
}

int	load_xpm(void *mlx, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(mlx, path, &img->size.x, &img->size.y);
	if (!img->img)
		return (0);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_len, &img->endian);
	return (1);
}

int	load_xpms(t_game *game)
{
	load_xpm(game->mlx_ptr, "textures/shift_tab.xpm", &game->img.misc[0]);
	load_xpm(game->mlx_ptr, "textures/bg_dither.xpm", &game->img.misc[1]);
	load_xpm(game->mlx_ptr, "textures/wall/wall1.xpm", &game->img.wall[0]);
	load_xpm(game->mlx_ptr, "textures/wall/wall2.xpm", &game->img.wall[1]);
	load_xpm(game->mlx_ptr, "textures/wall/wall3.xpm", &game->img.wall[2]);
	load_xpm(game->mlx_ptr, "textures/wall/wall4.xpm", &game->img.wall[3]);
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
			set_pixel(dst, x + origin.x, y + origin.y, color);
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
				set_pixel(dst, p.x, p.y, color);
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
				set_pixel(dst, p.x, p.y, color);
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
	err /= 2;
	max = 1000;
	while ((start.x != end.x || start.y != end.y) && max > 0)
	{
		brasenham(&err, &start, d, s);
		set_pixel(img, start.x, start.y, color);
		max--;
	}
}

void draw_diagonal_lines(t_img *img, t_point size, unsigned int color)
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

// void draw_triangle(t_img *img, t_triangle t, unsigned int color)
// {
// 	t_point		v1;
// 	t_point		v2;
// 	t_point		v3;
// 	int			half_size;

// 	half_size = t.size / 2;
// 	v1.x = t.origin.x + half_size * cos(t.angle * PI / 180);
// 	v1.y = t.origin.y + half_size * sin(t.angle * PI / 180);
// 	v2.x = t.origin.x + half_size * cos((t.angle + 120) * PI / 180);
// 	v2.y = t.origin.y + half_size * sin((t.angle + 120) * PI / 180);
// 	v3.x = t.origin.x + half_size * cos((t.angle + 240) * PI / 180);
// 	v3.y = t.origin.y + half_size * sin((t.angle + 240) * PI / 180);
// 	draw_line(img, v1, v2, color);
// 	draw_line(img, v2, v3, color);
// 	draw_line(img, v3, v1, color);
// }

void	draw_map_player(t_img *img, t_player p, t_point origin)
{
	t_point			player_pos;
	t_point			pointer_pos;
	float			dir_radius;
	float			dir_dist;

	player_pos.x = (int)((p.pos.x * (float)MAP_CELL_SIZE) + origin.x);
	player_pos.y = (int)((p.pos.y * (float)MAP_CELL_SIZE) + origin.y);
	draw_circle(img, player_pos, MAP_CELL_SIZE * 0.15, WHITE);
	draw_circle_outline(img, player_pos, MAP_CELL_SIZE * 0.25, WHITE);
	dir_radius = MAP_CELL_SIZE * 0.15;
	dir_dist = 0.25;
	pointer_pos.x = (int)((p.pos.x + (p.dir.x * dir_dist * p.zoom))
			* (float)MAP_CELL_SIZE) + origin.x;
	pointer_pos.y = (int)((p.pos.y + (p.dir.y * dir_dist * p.zoom))
			* (float)MAP_CELL_SIZE) + origin.y;
	draw_circle(img, pointer_pos, dir_radius, WHITE);
}

void	validate_input(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd("cub3D: Invalid number of arguments\n", 2);
		ft_putstr_fd("cub3D: usage: cub3D [*.cub]\n", 2);
		exit(1);
	}
	// if (open(av[1]) == -1) //check if able to open
	// 	;remove (void)av when this check is done
	(void)av;
}

void	ft_destroy_image(void *mlx_ptr, void **img)
{
	if (mlx_ptr && img && *img)
		mlx_destroy_image(mlx_ptr, *img);
	*img = NULL;
}

int	cleanup(t_game *game, unsigned char status, char *msg)
{
	ft_destroy_image(game->mlx_ptr, &game->img.wall[0].img);
	ft_destroy_image(game->mlx_ptr, &game->img.wall[1].img);
	ft_destroy_image(game->mlx_ptr, &game->img.wall[2].img);
	ft_destroy_image(game->mlx_ptr, &game->img.wall[3].img);
	ft_destroy_image(game->mlx_ptr, &game->img.misc[0].img);
	ft_destroy_image(game->mlx_ptr, &game->img.misc[1].img);
	ft_destroy_image(game->mlx_ptr, &game->img.win.img);
	ft_destroy_image(game->mlx_ptr, &game->img.map.img);
	ft_destroy_image(game->mlx_ptr, &game->img.map_mask.img);
	ft_destroy_image(game->mlx_ptr, &game->img.map_bg.img);
	ft_destroy_image(game->mlx_ptr, &game->img.ceiling.img);
	ft_destroy_image(game->mlx_ptr, &game->img.floor.img);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	game->win_ptr = NULL;
	if (game->mlx_ptr)
		mlx_destroy_display(game->mlx_ptr);
	ft_free_void(&game->mlx_ptr);
	ft_free(&game->frame.fps_str);
	if (msg)
		ft_putstr_fd(msg, 2);
	exit(status);
}

t_point	center(t_point origin, t_point size)
{
	origin.x -= size.x / 2;
	origin.y -= size.y / 2;
	return (origin);
}

int	init_bg(t_game *game, int ceiling, int floor)
{
	t_point	size;

	size.x = RES_X;
	size.y = RES_Y;
	if (init_img(game->mlx_ptr, &game->img.ceiling, RES_X, RES_Y) == -1
		|| init_img(game->mlx_ptr, &game->img.floor, RES_X, RES_Y) == -1)
		return (-1);
	draw_rectangle(&game->img.ceiling, (t_point){0, 0}, size, ceiling);
	draw_rectangle(&game->img.floor, (t_point){0, 0}, size, floor);
	return (0);
}

void	draw_map_tiles(t_img *map)
{
	t_point	count;
	t_point	origin;
	t_point	size;

	count.y = 0;
	origin.y = 0;
	size = (t_point){MAP_CELL_SIZE - 1, MAP_CELL_SIZE - 1};
	while (count.y < g_map_y)
	{
		origin.x = 0;
		count.x = 0;
		while (count.x < g_map_x)
		{
			if (g_map[count.y][count.x] == 1)
				draw_rectangle(map, origin, size, MAP_COLOR);
			else if (g_map[count.y][count.x] == 0)
				draw_rectangle(map, origin, size, BLACK);
			count.x++;
			origin.x += MAP_CELL_SIZE;
		}
		count.y++;
		origin.y += MAP_CELL_SIZE;
	}
}

int	init_minimap(t_game *game, t_point map_grid_size)
{
	t_point	map;
	t_point	mask;

	map.x = map_grid_size.x * MAP_CELL_SIZE;
	map.y = map_grid_size.y * MAP_CELL_SIZE;
	mask.x = 24 * MAP_CELL_SIZE / 2;
	mask.y = 24 * MAP_CELL_SIZE / 2;
	if (init_img(game->mlx_ptr, &game->img.map, map.x, map.y) == -1
		|| init_img(game->mlx_ptr, &game->img.map_mask, mask.x, mask.y) == -1
		|| init_img(game->mlx_ptr, &game->img.map_bg, mask.x, mask.y) == -1)
		return (-1);
	game->map.offset.x = RES_X - game->img.map_mask.size.x - RES_X / 50;
	game->map.offset.y = RES_X / 50;
	draw_rectangle(&game->img.map_bg, (t_point){0, 0}, game->img.map_mask.size,
		BLACK);
	draw_diagonal_lines(&game->img.map_bg, game->img.map_mask.size, 0x333333);
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

	center.x = RES_X / 2;
	center.y = RES_Y / 2;
	if (game->keys[MOUSE] == 0)
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, center.x, center.y);
	game->keys[MOUSE] = !game->keys[MOUSE];
}

void	pause_game(t_game *game)
{
	t_point	center;

	center.x = RES_X / 2;
	center.y = RES_Y / 2;
	if (game->keys[RUN])
		game->keys[PAUSE] = !game->keys[PAUSE];
	if (!game->keys[PAUSE] && game->keys[MOUSE])
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, center.x, center.y);
}

void	change_target_fps(unsigned int key, t_game *game)
{
	if (key == XK_bracketleft)
	{
		if (game->frame.fps_target > 30)
		{
			game->frame.fps_target -= 30;
			game->frame.time = 1000.0 / game->frame.fps_target;
		}
	}
	else if (key == XK_bracketright)
	{
		if (game->frame.fps_target < 90)
		{
			game->frame.fps_target += 30;
			game->frame.time = 1000.0 / game->frame.fps_target;
		}
	}
}

int	key_release(unsigned int key, t_game *game)
{
	if (key == XK_Up || key == XK_w)
		game->keys[UP] = 0;
	if (key == XK_Down || key == XK_s)
		game->keys[DOWN] = 0;
	if (key == XK_a)
		game->keys[LEFT] = 0;
	if (key == XK_d)
		game->keys[RIGHT] = 0;
	if (key == XK_r)
		game->keys[ROT_U] = 0;
	if (key == XK_f)
		game->keys[ROT_D] = 0;
	if (key == XK_Left || key == XK_q)
		game->keys[ROT_L] = 0;
	if (key == XK_Right || key == XK_e)
		game->keys[ROT_R] = 0;
	if (key == XK_Shift_L)
		game->keys[RUN] = 0;
	if (key == XK_Control_L)
		game->keys[CROUCH] = 0;
	if (key == XK_space)
		game->keys[JUMP] = 0;
	return (0);
}

int	key_press(unsigned int key, t_game *game)
{
	if (key == XK_Up || key == XK_w)
		game->keys[UP] = 1;
	if (key == XK_Down || key == XK_s)
		game->keys[DOWN] = 1;
	if (key == XK_a)
		game->keys[LEFT] = 1;
	if (key == XK_d)
		game->keys[RIGHT] = 1;
	if (key == XK_r)
		game->keys[ROT_U] = 1;
	if (key == XK_f)
		game->keys[ROT_D] = 1;
	if (key == XK_Left || key == XK_q)
		game->keys[ROT_L] = 1;
	if (key == XK_Right || key == XK_e)
		game->keys[ROT_R] = 1;
	if (key == XK_Shift_L)
		game->keys[RUN] = 1;
	if (key == XK_Control_L)
		game->keys[CROUCH] = 1;
	if (key == XK_space)
		game->keys[JUMP] = 1;
	if (key == XK_Tab)
		pause_game(game);
	if (key == XK_Escape)
		exit_game(game);
	if (key == XK_p)
		toggle_mouse(game);
	if (key == XK_m)
		game->keys[MAP] = -game->keys[MAP];
	change_target_fps(key, game);
	return (0);
}

void	vertical_look(t_game *game, float delta)
{
	const int	limit = RES_Y / 2;
	int			new;

	new = game->player.pitch + delta;
	if (new >= -limit && new <= limit)
		game->player.pitch += delta;
	if (game->player.pitch < -limit)
		game->player.pitch = -limit;
	else if (game->player.pitch > limit)
		game->player.pitch = limit;
}

void	handle_mouse(t_game *game)
{
	const t_point	center = {RES_X / 2, RES_Y / 2};
	t_point			mouse;
	float			old_dir_x;
	float			old_plane_x;
	t_point			delta;

	mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr, &mouse.x, &mouse.y);
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
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, center.x, center.y);
	}
}

void	calculate_movement(t_game *game, float *move_x, float *move_y)
{
	if (game->keys[UP])
	{
		*move_x += game->player.dir.x;
		*move_y += game->player.dir.y;
	}
	if (game->keys[DOWN])
	{
		*move_x -= game->player.dir.x;
		*move_y -= game->player.dir.y;
	}
	if (game->keys[LEFT])
	{
		*move_x += game->player.dir.y;
		*move_y -= game->player.dir.x;
	}
	if (game->keys[RIGHT])
	{
		*move_x -= game->player.dir.y;
		*move_y += game->player.dir.x;
	}
}

void	normalize_movement(float *move_x, float *move_y)
{
	float	length;

	length = sqrt(*move_x * *move_x + *move_y * *move_y);
	if (length > 0)
	{
		*move_x /= length;
		*move_y /= length;
	}
}

void	check_collision(t_game *game, t_fpoint new_pos, t_fpoint move, float radius)
{
	t_fpoint	side;

	if (move.x < 0)
		side.x = -radius;
	else
		side.x = radius;
	if (move.y < 0)
		side.y = -radius;
	else
		side.y = radius;
	if (g_map[(int)(game->player.pos.y)][(int)(new_pos.x - radius)] == 0
		&& g_map[(int)(game->player.pos.y - radius)][(int)(new_pos.x + side.x)] == 0
		&& g_map[(int)(game->player.pos.y + radius)][(int)(new_pos.x + side.x)] == 0)
		game->player.pos.x = new_pos.x;
	if (g_map[(int)(new_pos.y - radius)][(int)(game->player.pos.x)] == 0
		&& g_map[(int)(new_pos.y + side.y)][(int)(game->player.pos.x - radius)] == 0
		&& g_map[(int)(new_pos.y + side.y)][(int)(game->player.pos.x + radius)] == 0)
		game->player.pos.y = new_pos.y;
}

void	handle_movement_xy(t_game *game, float speed)
{
	t_fpoint	move;
	t_fpoint	new_pos;
	float		radius;

	if (!game->keys[UP] && !game->keys[DOWN] && !game->keys[LEFT] && !game->keys[RIGHT])
		return ;
	radius = 0.25;
	move.x = 0;
	move.y = 0;
	calculate_movement(game, &move.x, &move.y);
	normalize_movement(&move.x, &move.y);
	new_pos.x = game->player.pos.x + move.x * speed;
	new_pos.y = game->player.pos.y + move.y * speed;
	check_collision(game, new_pos, move, radius);
}

void	handle_movement_z(t_game *game)
{
	if (game->keys[CROUCH])
	{
		game->player.height -= 0.05;
		if (game->player.height < P_MIN_HEIGHT)
			game->player.height = P_MIN_HEIGHT;
	}
	if (game->keys[JUMP])
	{
		game->player.height += 0.05;
		if (game->player.height > P_MAX_HEIGHT)
			game->player.height = P_MAX_HEIGHT;
	}
}

void	handle_yaw(t_game *game, float speed)
{
	float			old_dir_x;
	float			old_plane_x;

	if (game->keys[ROT_L] && game->keys[ROT_R])
		return ;
	old_dir_x = game->player.dir.x;
	old_plane_x = game->player.plane.x;
	if (game->keys[ROT_L])
	{
		game->player.dir.x = game->player.dir.x * cos(-speed) - game->player.dir.y * sin(-speed);
		game->player.dir.y = old_dir_x * sin(-speed) + game->player.dir.y * cos(-speed);
		game->player.plane.x = game->player.plane.x * cos(-speed) - game->player.plane.y * sin(-speed);
		game->player.plane.y = old_plane_x * sin(-speed) + game->player.plane.y * cos(-speed);
	}
	else if (game->keys[ROT_R])
	{
		game->player.dir.x = game->player.dir.x * cos(speed) - game->player.dir.y * sin(speed);
		game->player.dir.y = old_dir_x * sin(speed) + game->player.dir.y * cos(speed);
		game->player.plane.x = game->player.plane.x * cos(speed) - game->player.plane.y * sin(speed);
		game->player.plane.y = old_plane_x * sin(speed) + game->player.plane.y * cos(speed);
	}
}

void	handle_pitch(t_game *game)
{
	const int	limit = RES_Y / 2;

	if (game->keys[ROT_U] && game->keys[ROT_D])
		return ;
	if (game->keys[ROT_U])
		game->player.pitch -= game->frame.time;
	else if (game->keys[ROT_D])
		game->player.pitch += game->frame.time;
	if (game->player.pitch < -limit)
		game->player.pitch = -limit;
	else if (game->player.pitch > limit)
		game->player.pitch = limit;
}

int	handle_keys(t_game *game)
{
	int	run_speed;

	run_speed = 1;
	if (game->keys[RUN] == 1 && game->keys[UP])
		run_speed = RUN_SPD;
	handle_movement_xy(game, MOV_SPD * game->frame.time * run_speed);
	handle_movement_z(game);
	handle_pitch(game);
	handle_yaw(game, ROT_SPD * game->frame.time);
	return (0);
}

void	init_keystate(t_game *game)
{
	int	i;

	i = 0;
	while (i < (int)(sizeof(game->keys) / sizeof(*game->keys)))
	{
		game->keys[i] = 0;
		i++;
	}
	game->keys[MAP] = 1;
	game->keys[MOUSE] = 1;
}

int	a_second_has_passed(void)
{
	static struct timeval	start_time;
	struct timeval			current_time;
	long					seconds_elapsed;

	if (start_time.tv_sec == 0)
	{
		gettimeofday(&start_time, NULL);
		return (0);
	}
	gettimeofday(&current_time, NULL);
	seconds_elapsed = current_time.tv_sec - start_time.tv_sec;
	if (seconds_elapsed >= 1)
	{
		start_time = current_time;
		return (1);
	}
	return (0);
}

int	should_render_frame(t_game *game)
{
	static int	fps = 0;
	long		elapsed;

	gettimeofday(&game->frame.current, NULL);
	elapsed = (game->frame.current.tv_sec - game->frame.last.tv_sec) * 1000
		+ (game->frame.current.tv_usec - game->frame.last.tv_usec) / 1000;
	if (elapsed >= game->frame.time)
	{
		fps++;
		game->frame.last = game->frame.current;
		if (a_second_has_passed())
		{
			ft_free(&game->frame.fps_str);
			game->frame.fps_str = ft_itoa(fps);
			fps = 0;
		}
		return (1);
	}
	return (0);
}

void	draw_minimap(t_game *game)
{
	t_fpoint	player_pos;

	player_pos.x = (int)((game->player.pos.x * (float)MAP_CELL_SIZE));
	player_pos.y = (int)((game->player.pos.y * (float)MAP_CELL_SIZE));
	draw_rectangle(&game->img.map, (t_point){0, 0}, game->img.map.size,
		MAP_COLOR);
	draw_map_tiles(&game->img.map);
	draw_map_player(&game->img.map, game->player,
		(t_point){0, 0});
	put_img((t_point){0, 0,}, &game->img.map_bg, &game->img.map_mask);
	put_img((t_point){-player_pos.x + game->img.map_mask.size.x / 2, -player_pos.y + game->img.map_mask.size.y / 2},
		&game->img.map, &game->img.map_mask);
	put_img(game->map.offset, &game->img.map_mask,
		&game->img.win);
}

int	out_of_bounds(t_point map)
{
	if (map.x < 0 || map.y < 0 || map.x > g_map_x || map.y > g_map_y)
		return (1);
	return (0);
}

unsigned int	multiply_color(unsigned int color, float factor)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = (color >> 0) & 0xFF;
	r *= factor;
	g *= factor;
	b *= factor;
	return ((r << 16) | (g << 8) | b);
}

float	get_light_intensity(t_light *light, float dist)
{
	float	intensity;

	intensity = (light->max - dist) / (light->max - light->min);
	if (intensity < 0)
		intensity = 0;
	if (intensity > 1)
		intensity = 1;
	intensity = intensity * (1 - light->ambient) + light->ambient;
	return (intensity);
}

void	render_viewport(t_game *game)
{
	const float		camera_x_factor = 2.0 / RES_X;
	float			camera_x;
	int				x;
	t_point			map;
	t_fpoint		ray_dir;
	t_fpoint		side_dist;
	t_fpoint		delta_dist;
	float			perp_wall_dist;
	t_point			step;
	int				hit;
	int				side;
	double			line_height;
	int				draw_start;
	int				draw_end;

	put_img((t_point){0, 0}, &game->img.ceiling, &game->img.win);
	put_img((t_point){0, RES_Y / 2 - game->player.pitch}, &game->img.floor, &game->img.win);
	put_img_scale((t_point){0, RES_Y / 2 - game->player.pitch}, &game->img.misc[1], &game->img.win, 
				(t_fpoint){1, 1 - (0.4 - game->player.height) / (0.5 - -0.4)});
	x = 0;
	while (x < RES_X)
	{
		camera_x = (x * camera_x_factor - 1);
		ray_dir.x = game->player.dir.x * game->player.zoom + game->player.plane.x * camera_x;
		ray_dir.y = game->player.dir.y * game->player.zoom + game->player.plane.y * camera_x;
		map.x = (int)game->player.pos.x;
		map.y = (int)game->player.pos.y;
		if (ray_dir.x == 0)
			delta_dist.x = 1E+37;
		else
			delta_dist.x = fabsf(1 / ray_dir.x);
		if (ray_dir.y == 0)
			delta_dist.y = 1E+37;
		else
			delta_dist.y = fabsf(1 / ray_dir.y);
		if (ray_dir.x < 0)
		{
			step.x = -1;
			side_dist.x = (game->player.pos.x - map.x) * delta_dist.x;
		}
		else
		{
			step.x = 1;
			side_dist.x = (map.x + 1.0 - game->player.pos.x) * delta_dist.x;
		}
		if (ray_dir.y < 0)
		{
			step.y = -1;
			side_dist.y = (game->player.pos.y - map.y) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (map.y + 1.0 - game->player.pos.y) * delta_dist.y;
		}
		hit = 0;
		while (hit == 0)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map.x += step.x;
				side = VERTICAL;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map.y += step.y;
				side = HORIZONTAL;
			}
			if (out_of_bounds(map))
				return ;
			if (g_map[map.y][map.x] > 0)
				hit = 1;
		}
		if (side == VERTICAL)
			perp_wall_dist = (side_dist.x - delta_dist.x);
		else
			perp_wall_dist = (side_dist.y - delta_dist.y);
		line_height = (int)(RES_Y / perp_wall_dist);
		draw_start = -line_height / 2 + RES_Y / 2 - game->player.pitch + (line_height * game->player.height);
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + RES_Y / 2 - game->player.pitch + (line_height * game->player.height);
		if (draw_end >= RES_Y)
			draw_end = RES_Y;
		float wall_x;
		t_point	tex;
		float	tex_step;
		float	tex_pos;
		int	y;
		if (side == 0)
			wall_x = game->player.pos.y + perp_wall_dist * ray_dir.y;
		else
			wall_x = game->player.pos.x + perp_wall_dist * ray_dir.x;
		wall_x -= floorf(wall_x);
		tex.x = (int)(wall_x * WALL);
		t_img	*wall_tex;
		if (side == VERTICAL)
		{
			wall_tex = &game->img.wall[EAST];
			if (ray_dir.x <= 0)
			{
				wall_tex = &game->img.wall[WEST];
				tex.x = WALL - tex.x - 1;
			}
		}
		else if (side == HORIZONTAL)
		{
			wall_tex = &game->img.wall[NORTH];
			if (ray_dir.y >= 0)
			{
				wall_tex = &game->img.wall[SOUTH];
				tex.x = WALL - tex.x - 1;
			}
		}
		tex_step = 1.0 * WALL / line_height;
		y = draw_start;
		tex_pos = (draw_start + game->player.pitch - (line_height * game->player.height) - RES_Y / 2 + line_height / 2) * tex_step;
		float intensity = get_light_intensity(&game->light, perp_wall_dist * game->player.zoom);
		while (y < draw_end)
		{
			tex.y = (int)tex_pos & (WALL - 1);
			unsigned int	color = get_pixel(wall_tex, tex.x, tex.y);
			color = multiply_color(get_pixel(wall_tex, tex.x, tex.y), intensity);
			tex_pos += tex_step;
			set_pixel(&game->img.win, x, y, color);
			y++;
		}
		x++;
	}
}

void	display_fps_counter(t_game *game)
{
	if (game->frame.fps_str)
	{
		mlx_string_put(game->mlx_ptr, game->win_ptr, 4, 13, WHITE,
			game->frame.fps_str);
		mlx_string_put(game->mlx_ptr, game->win_ptr, 20, 13, WHITE,
			"FPS");
	}
	else
		mlx_string_put(game->mlx_ptr, game->win_ptr, 4, 13, WHITE,
			"INITIALIZING FPS...");
}

int	game_loop(t_game *game)
{
	if (game->keys[MOUSE] && !game->keys[PAUSE])
		handle_mouse(game);
	if (should_render_frame(game))
	{
		if (game->keys[PAUSE])
		{
			put_img((t_point){0, 0}, &game->img.misc[0], &game->img.win);
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.win.img, 0, 0);
		}
		else
		{
			handle_keys(game);
			render_viewport(game);
			if (game->keys[MAP] == 1)
				draw_minimap(game);
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
				game->img.win.img, 0, 0);
			// update_lighting()
		}
		if (game->keys[MOUSE] == 0)
			mlx_string_put(game->mlx_ptr, game->win_ptr, 4, 26, WHITE,
				"MOUSE DISABLED");
		display_fps_counter(game);
		if (out_of_bounds((t_point){(int)game->player.pos.x, (int)game->player.pos.y}))
			cleanup(game, 0, "cub3D: Out of bounds\n");
	}
	return (0);
}

void	init_player_plane(t_player *player)
{
	if (player->dir.x != 0)
	{
		player->plane.x = 0;
		if (player->dir.x > 0)
			player->plane.y = 0.66;
		else
			player->plane.y = -0.66;
	}
	else
	{
		if (player->dir.y > 0)
			player->plane.x = -0.66;
		else
			player->plane.x = 0.66;
		player->plane.y = 0;
	}
}

void	init_player(t_player *player)
{
	t_fpoint	pos;

	pos.x = 8;
	pos.y = 6;
	player->pitch = 0;
	player->pos.x = pos.x + 0.5;
	player->pos.y = pos.y + 0.5;
	player->dir.x = 0;
	player->dir.y = -1;
	player->zoom = 1.0;
	player->height = 0.0;
	init_player_plane(player);
}

void	init_framedata(t_frame_data *frame)
{
	frame->fps_target = 60;
	frame->time = 1000.0 / frame->fps_target;
	gettimeofday(&frame->last, NULL);
}

void	init_game_struct(t_game *game)
{
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->img.win.img = NULL;
	game->img.view.img = NULL;
	game->img.map.img = NULL;
	game->img.map_mask.img = NULL;
	game->img.map_bg.img = NULL;
	game->img.ceiling.img = NULL;
	game->img.floor.img = NULL;
	game->frame.fps_str = NULL;
}

int	init_game(t_game *game)
{
	// game->map.size.x = (n rows);
	// game->map.size.y = (n columns);
	// game->map.grid = malloc(game->map.size.y * sizeof(int *));
	init_game_struct(game);
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
		return (-1);
	game->win_ptr = mlx_new_window(game->mlx_ptr, RES_X, RES_Y, "cub3D");
	if (game->win_ptr == NULL)
		return (-1);
	if (init_img(game->mlx_ptr, &game->img.win, RES_X, RES_Y) == -1)
		return (-1);
	if (init_minimap(game, (t_point){g_map_x, g_map_y}) == -1
		|| init_bg(game, BLACK, 0x2C2E33) == -1)
		return (-1);
	init_framedata(&game->frame);
	init_keystate(game);
	init_player(&game->player);
	game->light.min = 0.25;
	game->light.max = 2.5;
	game->light.ambient = 0.25;
	load_xpms(game);
	mlx_mouse_move(game->mlx_ptr, game->win_ptr, RES_X / 2, RES_Y / 2);
	return (0);
}

int mwheel(unsigned int key, int x, int y, t_game *game)
{
	const float	step = 0.1;
	const int	pitch_limit = RES_Y / 2;

	(void)x;
	(void)y;
	if (key == 4 && game->player.zoom < 2)
	{
		game->player.zoom += step;
		if (game->player.pitch != pitch_limit && game->player.pitch != -pitch_limit)
			game->player.pitch *= game->player.zoom / (game->player.zoom - step);
	}
	else if (key == 5 && game->player.zoom > 1)
	{
		game->player.zoom -= step;
		if (game->player.pitch != pitch_limit && game->player.pitch != -pitch_limit)
			game->player.pitch *= game->player.zoom / (game->player.zoom + step);
		if (game->player.pitch > pitch_limit)
			game->player.pitch = pitch_limit;
		else if (game->player.pitch < -pitch_limit)
			game->player.pitch = -pitch_limit;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	validate_input(ac, av);
	if (init_game(&game) == -1)
		return (cleanup(&game, 1, "cub3D: Error initializing game\n"));
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, &key_press, &game);
	mlx_hook(game.win_ptr, KeyRelease, KeyReleaseMask, &key_release, &game);
	mlx_hook(game.win_ptr, ButtonPress, ButtonPressMask, &mwheel, &game);
	mlx_hook(game.win_ptr, DestroyNotify, StructureNotifyMask, &exit_game, &game);
	mlx_loop_hook(game.mlx_ptr, &game_loop, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
