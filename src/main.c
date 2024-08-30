/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:44:00 by jaslim            #+#    #+#             */
/*   Updated: 2024/08/30 16:58:52 by jaslim           ###   ########.fr       */
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
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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

t_img	init_img(void *mlx_ptr, int width, int height)
{
	t_img	img;

	img.img = mlx_new_image(mlx_ptr, width, height);
	if (img.img == NULL)
	{
		img.addr = NULL;
		return (img);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_len, &img.endian);
	img.size.x = width;
	img.size.y = height;
	return (img);
}

void	set_pixel(t_img *img, int x, int y, unsigned int color)
{
	char			*dst;

	if (x < 0 || y < 0 || x > RES_X || y > RES_Y || (color >> 24) & 0xFF)
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

void	put_img(t_point origin, t_point size, t_img *src, t_img *dst)
{
	int		x;
	int		y;

	y = 0;
	if (origin.x < 0 || origin.y < 0
		|| (origin.x + size.x) > (dst->line_len / (dst->bits_per_pixel / 8))
		|| (origin.y + size.y) > (dst->line_len / (dst->bits_per_pixel / 8)))
		return ;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			set_pixel(dst, x + origin.x, y + origin.y, get_pixel(src, x, y));
			x++;
		}
		y++;
	}
}

int	load_xpm(void *mlx, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(mlx, path, &img->size.x, &img->size.y);
	if (!img->img)
		return (-1);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_len, &img->endian);
	return (0);
}

int	load_xpms(t_game *game)
{
	if (load_xpm(game->mlx_ptr, "textures/wall/wall1.xpm", &game->sprites.wall[0]) == -1)
		return (-1);
	put_img((t_point){RES_X / 2 - (game->sprites.wall[0].size.x / 2), RES_Y / 2 - (game->sprites.wall[0].size.y / 2)}, game->sprites.wall[0].size, &game->sprites.wall[0], &game->win);
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

void draw_triangle(t_img *img, t_triangle t, unsigned int color)
{
	t_point		v1;
	t_point		v2;
	t_point		v3;
	int			half_size;

	half_size = t.size / 2;
	v1.x = t.origin.x + half_size * cos(t.angle * PI / 180);
	v1.y = t.origin.y + half_size * sin(t.angle * PI / 180);
	v2.x = t.origin.x + half_size * cos((t.angle + 120) * PI / 180);
	v2.y = t.origin.y + half_size * sin((t.angle + 120) * PI / 180);
	v3.x = t.origin.x + half_size * cos((t.angle + 240) * PI / 180);
	v3.y = t.origin.y + half_size * sin((t.angle + 240) * PI / 180);
	draw_line(img, v1, v2, color);
	draw_line(img, v2, v3, color);
	draw_line(img, v3, v1, color);
}

// RES_X - game->map.size.x, 0}
void	draw_map_player(t_img *img, t_player p, t_point origin)
{
	static float	scale = (float)MAP_CELL_SIZE;
	t_point			player_pos;
	t_point			pointer_pos;
	float			dir_radius;
	float			dir_dist;

	player_pos.x = (int)((p.pos.x * scale) + origin.x);
	player_pos.y = (int)((p.pos.y * scale) + origin.y);
	draw_circle(img, player_pos, MAP_CELL_SIZE * 0.15, WHITE);
	draw_circle_outline(img, player_pos, MAP_CELL_SIZE * 0.25, WHITE);
	dir_radius = MAP_CELL_SIZE * 0.15;
	dir_dist = 0.25;
	pointer_pos.x = (int)((p.pos.x + (p.dir.x * dir_dist)) * scale) + origin.x;
	pointer_pos.y = (int)((p.pos.y + (p.dir.y * dir_dist)) * scale) + origin.y;
	draw_circle(img, pointer_pos, dir_radius, WHITE);
}

int	input_validation(int ac, char **av)
{
	if (ac != 2)
	{
		ft_printf("cub3D: Invalid number of arguments\n");
		ft_printf("cub3D: usage: cub3D [*.cub]\n");
		return (-1);
	}
	// if (open(av[1]) == -1)
	// 	;
	(void)av;
	return (0);
}

int	cleanup(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->win.img);
	mlx_destroy_image(game->mlx_ptr, game->map.img);
	mlx_destroy_image(game->mlx_ptr, game->bg.img);
	mlx_destroy_image(game->mlx_ptr, game->view.img);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	ft_free_void(&game->mlx_ptr);
	ft_free(&game->fps);
	exit(0);
}

t_point	center(t_point origin, t_point size)
{
	origin.x -= size.x / 2;
	origin.y -= size.y / 2;
	return (origin);
}

t_img	init_bg(void *mlx_ptr)
{
	t_img	bg;
	t_point	size;

	size.x = RES_X;
	size.y = RES_Y / 2;
	bg = init_img(mlx_ptr, RES_X, RES_Y);
	// if (bg.img == NULL)
	// 	;//handle it
	draw_rectangle(&bg, (t_point){0, 0}, size, 0x171B22);
	draw_rectangle(&bg, (t_point){0, RES_Y / 2}, size, 0x3B3E44);
	return (bg);
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

t_img	init_minimap(t_game *game, t_point map_grid_size)
{
	t_img	map;
	t_point	map_size;

	map_size.x = map_grid_size.x * MAP_CELL_SIZE;
	map_size.y = map_grid_size.y * MAP_CELL_SIZE;
	map = init_img(game->mlx_ptr, map_size.x, map_size.y);
	return (map);
}

int	key_esc(t_game *game)
{
	ft_printf("exit\n");
	cleanup(game);
	return (0);
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
	if (key == XK_Left || key == XK_q)
		game->keys[ROT_L] = 0;
	if (key == XK_Right || key == XK_e)
		game->keys[ROT_R] = 0;
	return (0);
}

void	pause_game(t_game *game)
{
	static t_point	center = {RES_X / 2, RES_Y / 2};

	if (game->pause == 1)
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, center.x, center.y);
	game->pause = -game->pause;
}

int	key_press(unsigned int key, t_game *game)
{
	if (key == XK_Escape)
		key_esc(game);
	if (key == XK_p)
		pause_game(game);
	if (key == XK_bracketleft)
	{
		if (game->target_fps > 30)
		{
			game->target_fps -= 30;
			game->frame_time = 1000 / game->target_fps;
		}
	}
	if (key == XK_bracketright)
	{
		if (game->target_fps < 90)
		{
			game->target_fps += 30;
			game->frame_time = 1000 / game->target_fps;
		}
	}
	if (key == XK_Up || key == XK_w)
		game->keys[UP] = 1;
	if (key == XK_Down || key == XK_s)
		game->keys[DOWN] = 1;
	if (key == XK_a)
		game->keys[LEFT] = 1;
	if (key == XK_d)
		game->keys[RIGHT] = 1;
	if (key == XK_Left || key == XK_q)
		game->keys[ROT_L] = 1;
	if (key == XK_Right || key == XK_e)
		game->keys[ROT_R] = 1;
	if (key == XK_m)
		game->map_toggle *= -1;
	return (0);
}

// void	handle_mouse(t_game *game)
// {
// 	static t_point	center = {RES_X / 2, RES_Y / 2};
// 	int				delta_x;
// 	t_point			mouse;
// 	float			old_dir_x;
// 	float			old_plane_x;

// 	mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr, &mouse.x, &mouse.y);
// 	delta_x = mouse.x - center.x;
// 	old_dir_x = game->player.dir.x;
// 	old_plane_x = game->player.plane.x;
// 	if (delta_x != 0)
// 	{
// 		game->player.dir.x = game->player.dir.x * cos(MOUSE_SEN) - game->player.dir.y * sin(MOUSE_SEN);
// 		game->player.dir.y = old_dir_x * sin(MOUSE_SEN) + game->player.dir.y * cos(MOUSE_SEN);
// 		game->player.plane.x = game->player.plane.x * cos(MOUSE_SEN) - game->player.plane.y * sin(MOUSE_SEN);
// 		game->player.plane.y = old_plane_x * sin(MOUSE_SEN) + game->player.plane.y * cos(MOUSE_SEN);
// 		mlx_mouse_move(game->mlx_ptr, game->win_ptr, center.x, center.y);
// 	}
// }

void	handle_mouse(t_game *game)
{
	static t_point	center = {RES_X / 2, RES_Y / 2};
	t_point			mouse;
	int				delta_x;
	float			old_dir_x;
	float			old_plane_x;

	mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr, &mouse.x, &mouse.y);
	delta_x = mouse.x - center.x;
	if (delta_x != 0)
	{
		old_dir_x = game->player.dir.x;
		old_plane_x = game->player.plane.x;
		game->player.dir.x = game->player.dir.x * cos(MOUSE_SEN * delta_x)
			- game->player.dir.y * sin(MOUSE_SEN * delta_x);
		game->player.dir.y = old_dir_x * sin(MOUSE_SEN * delta_x)
			+ game->player.dir.y * cos(MOUSE_SEN * delta_x);
		game->player.plane.x = game->player.plane.x * cos(MOUSE_SEN * delta_x)
			- game->player.plane.y * sin(MOUSE_SEN * delta_x);
		game->player.plane.y = old_plane_x * sin(MOUSE_SEN * delta_x)
			+ game->player.plane.y * cos(MOUSE_SEN * delta_x);
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, center.x, center.y);
	}
}

void	handle_rotation(t_game *game, float speed)
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

void	handle_movement(t_game *game, float speed)
{
	t_fpoint	move;
	t_fpoint	new_pos;
	float	radius;

	radius = 0.1;
	move.x = 0;
	move.y = 0;
	calculate_movement(game, &move.x, &move.y);
	normalize_movement(&move.x, &move.y);
	new_pos.x = (game->player.pos.x + move.x * speed);
	new_pos.y = (game->player.pos.y + move.y * speed);
	if (move.x < 0)
	{
		if (g_map[(int)(game->player.pos.y)][(int)(new_pos.x - radius)] == 0
			&& g_map[(int)(game->player.pos.y - radius)][(int)(new_pos.x - radius)] == 0
			&& g_map[(int)(game->player.pos.y + radius)][(int)(new_pos.x - radius)] == 0)
			game->player.pos.x = new_pos.x;
	}
	else
	{
		if (g_map[(int)(game->player.pos.y)][(int)(new_pos.x + radius)] == 0
			&& g_map[(int)(game->player.pos.y - radius)][(int)(new_pos.x + radius)] == 0
			&& g_map[(int)(game->player.pos.y + radius)][(int)(new_pos.x + radius)] == 0)
			game->player.pos.x = new_pos.x;
	}
	if (move.y < 0)
	{
		if (g_map[(int)(new_pos.y - radius)][(int)(game->player.pos.x)] == 0
			&& g_map[(int)(new_pos.y - radius)][(int)(game->player.pos.x - radius)] == 0
			&& g_map[(int)(new_pos.y - radius)][(int)(game->player.pos.x + radius)] == 0)
			game->player.pos.y = new_pos.y;
	}
	else
		if (g_map[(int)(new_pos.y + radius)][(int)(game->player.pos.x)] == 0
			&& g_map[(int)(new_pos.y + radius)][(int)(game->player.pos.x - radius)] == 0
			&& g_map[(int)(new_pos.y + radius)][(int)(game->player.pos.x + radius)] == 0)
			game->player.pos.y = new_pos.y;
}

int	handle_keys(t_game *game)
{
	handle_rotation(game, ROT_SPD * game->frame_time);
	handle_movement(game, MOV_SPD * game->frame_time);
	return (0);
}

void	init_keys(t_game *game)
{
	int	i;

	i = 0;
	while (i <= (int)sizeof(game->keys))
	{
		game->keys[i] = 0;
		i++;
	}
	game->map_toggle = 1;
	game->pause = -1;
}

int	a_second_has_passed(void)
{
	static struct timeval	start_time;
	struct timeval			current_time;
	long					seconds_elapsed;

	if (start_time.tv_sec == 0 && start_time.tv_usec == 0)
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

	gettimeofday(&game->current_frame, NULL);
	elapsed = (game->current_frame.tv_sec - game->last_frame.tv_sec) * 1000
		+ (game->current_frame.tv_usec - game->last_frame.tv_usec) / 1000;
	if (elapsed >= game->frame_time)
	{
		fps++;
		game->last_frame = game->current_frame;
		if (a_second_has_passed())
		{
			ft_free(&game->fps);
			game->fps = ft_itoa(fps);
			fps = 0;
		}
		return (1);
	}
	return (0);
}

// int	should_render_frame(t_game *game)
// {
// 	static int	frame_time = 1000 / FRAME_RATE;
// 	static int	fps = 0;
// 	long		elapsed;

// 	gettimeofday(&game->current_frame, NULL);
// 	elapsed = (game->current_frame.tv_sec - game->last_frame.tv_sec) * 1000
// 		+ (game->current_frame.tv_usec - game->last_frame.tv_usec) / 1000;
// 	if (elapsed >= frame_time)
// 	{
// 		fps++;
// 		game->last_frame = game->current_frame;
// 		if (a_second_has_passed())
// 		{
// 			ft_free(&game->fps);
// 			game->fps = ft_itoa(fps);
// 			fps = 0;
// 		}
// 		return (1);
// 	}
// 	return (0);
// }

//GPT
void rotate_image(t_img *src, t_img *dst, float angle)
{
    int x, y;
    int center_x = src->size.x / 2;
    int center_y = src->size.y / 2;
    float cos_a = cos(angle);
    float sin_a = sin(angle);

    for (y = 0; y < src->size.y; y++)
    {
        for (x = 0; x < src->size.x; x++)
        {
            int new_x = cos_a * (x - center_x) - sin_a * (y - center_y) + center_x;
            int new_y = sin_a * (x - center_x) + cos_a * (y - center_y) + center_y;

            if (new_x >= 0 && new_x < dst->size.x && new_y >= 0 && new_y < dst->size.y)
            {
                unsigned int color = get_pixel(src, x, y); // Assume get_pixel reads a pixel color
                set_pixel(dst, new_x, new_y, color);      // Assume set_pixel sets a pixel color
            }
        }
    }
}

void	draw_minimap(t_game *game)
{
	draw_rectangle(&game->map, (t_point){0, 0}, game->map.size, MAP_COLOR);
	draw_map_tiles(&game->map);
	draw_map_player(&game->map, game->player,
		(t_point){0, 0});
	// rotate_image(&game->map, &game->map, atan2f(game->player.dir.x, game->player.dir.y));
	put_img(game->map_offset, game->map.size, &game->map, &game->win);
}

// void	handle_mouse(t_game *game)
// {
// 	static t_point	center = {RES_X / 2, RES_Y / 2};
// 	int				delta_x;
// 	t_point			mouse;

// 	mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr, &mouse.x, &mouse.y);
// 	delta_x = mouse.x - center.x;
// 	if (delta_x != 0)
// 	{
// 		game->player.angle += delta_x * MOUSE_SEN;
// 		if (game->player.angle < 0)
// 			game->player.angle += PI2;
// 		else if (game->player.angle > PI2)
// 			game->player.angle -= PI2;
// 		game->player.dir.x = cos(game->player.angle);
// 		game->player.dir.y = sin(game->player.angle);
// 		mlx_mouse_move(game->mlx_ptr, game->win_ptr, center.x, center.y);
// 	}
// }

int	not_out_of_bounds(t_point map)
{
	if (map.x < 0 || map.y < 0 || map.x > g_map_x || map.y > g_map_y)
		return (0);
	return (1);
}

void	lodev(t_game *game)
{
	int				x;
	float			camera_x;
	t_point			map;
	t_fpoint		ray_dir;
	t_fpoint		side_dist;
	t_fpoint		delta_dist;
	float			perp_wall_dist;
	t_point			step;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	unsigned int	color;

	x = 0;
	while (x < RES_X)
	{
		camera_x = 2 * x / (float)RES_X - 1;
		ray_dir.x = game->player.dir.x + game->player.plane.x * camera_x;
		ray_dir.y = game->player.dir.y + game->player.plane.y * camera_x;
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
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map.y += step.y;
				side = 1;
			}
			if (g_map[map.y][map.x] > 0)
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (side_dist.x - delta_dist.x);
		else
			perp_wall_dist = (side_dist.y - delta_dist.y);
		line_height = (int)(RES_Y / perp_wall_dist);
		draw_start = -line_height / 2 + RES_Y / 2;
		if (draw_start < 0)
			draw_start = -1;
		draw_end = line_height / 2 + RES_Y / 2;
		if (draw_end >= RES_Y)
			draw_end = RES_Y - 1;
		color = 0xAAAAAA;
		if (side == 1)
			color = 0x888888;
		draw_line(&game->view,
			(t_point){x, draw_start},
			(t_point){x, draw_end}, color);
		x++;
	}
	// printf("player dir x:%f\n", game->player.dir.x);
	// printf("player dir y:%f\n", game->player.dir.y);
	// printf("player plane x:%f\n", game->player.plane.x);
	// printf("player plane y:%f\n", game->player.plane.y);
}

int	game_loop(t_game *game)
{
	if (game->pause != 1)
		handle_mouse(game);
	if (should_render_frame(game))
	{
		put_img((t_point){0, 0}, game->bg.size, &game->bg, &game->view);
		lodev(game);
		handle_keys(game);
		put_img((t_point){0, 0}, game->view.size, &game->view, &game->win);
		if (game->map_toggle == 1)
			draw_minimap(game);
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->win.img,
			0, 0);
		if (game->fps)
			mlx_string_put(game->mlx_ptr, game->win_ptr, 1, 11, WHITE,
				game->fps);
	}
	return (0);
}

void	init_player_pos(t_game *game)
{
	t_fpoint	pos;

	pos.x = 1;
	pos.y = 1;
	game->player.pos.x = pos.x + 0.5;
	game->player.pos.y = pos.y + 0.5;
	game->player.dir.x = 1;
	game->player.dir.y = 0;
	game->player.plane.x = 0.66;
	game->player.plane.y = 0.66;
	if (game->player.dir.x)
		game->player.plane.x = 0;
	else
		game->player.plane.y = 0;
}

int	main(int ac, char **av)
{
	t_game	game;

	if (input_validation(ac, av) == -1)
		return (1);
	game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr, RES_X, RES_Y, "cub3D");
	mlx_mouse_move(game.mlx_ptr, game.win_ptr, RES_X / 2, RES_Y / 2);
	game.win = init_img(game.mlx_ptr, RES_X, RES_Y);
	game.view = init_img(game.mlx_ptr, RES_X, RES_Y);
	game.bg = init_bg(game.mlx_ptr);
	game.map = init_minimap(&game, (t_point){g_map_x, g_map_y});
	game.map_offset.x = RES_X - game.map.size.x - RES_X / 50;
	game.map_offset.y = RES_X / 50;
	game.fps = NULL;
	game.target_fps = 60;
	game.frame_time = 1000 / game.target_fps;
	init_keys(&game);
	init_player_pos(&game);
	gettimeofday(&game.last_frame, NULL);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, &key_press, &game);
	mlx_hook(game.win_ptr, KeyRelease, KeyReleaseMask, &key_release, &game);
	mlx_hook(game.win_ptr, DestroyNotify, StructureNotifyMask, &key_esc, &game);
	mlx_loop_hook(game.mlx_ptr, &game_loop, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
