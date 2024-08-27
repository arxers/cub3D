/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:44:00 by jaslim            #+#    #+#             */
/*   Updated: 2024/08/27 21:37:09 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	g_map_x = 8;
int	g_map_y = 8;
int	g_map[10][10] = {
	{1,1,1,1,1,1,1,1},
	{1,0,1,0,1,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,1},
	{1,0,1,0,0,1,1,1},
	{1,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1}
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

void	draw_circle_outline(t_img *img, t_point origin, int radius,
	unsigned int color)
{
	int		x;
	int		y;
	float	angle;

	angle = 0;
	while (angle < 360)
	{
		x = origin.x + radius * cos(angle * PI / 180);
		y = origin.y + radius * sin(angle * PI / 180);
		set_pixel(img, x, y, color);
		angle += 0.1;
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
	static float	scale = (float)MINIMAP_CELL / MAP_CELL;
	t_point			player_pos;
	t_point			pointer_pos;
	float			pointer_radius;
	float			pointer_dist;

	player_pos.x = (int)((p.x * scale) + origin.x);
	player_pos.y = (int)((p.y * scale) + origin.y);
	draw_circle(img, player_pos, MINIMAP_CELL * 0.25, WHITE);
	pointer_radius = MINIMAP_CELL * 0.15;
	pointer_dist = MAP_CELL * 0.25;
	pointer_pos.x = (int)((p.x + (p.dx * pointer_dist)) * scale) + origin.x;
	pointer_pos.y = (int)((p.y + (p.dy * pointer_dist)) * scale) + origin.y;
	draw_circle(img, pointer_pos, pointer_radius, WHITE);
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
	ft_free(&game->mlx_ptr);
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
	size = (t_point){MINIMAP_CELL - 1, MINIMAP_CELL - 1};
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
			origin.x += MINIMAP_CELL;
		}
		count.y++;
		origin.y += MINIMAP_CELL;
	}
}

t_img	init_map(t_game *game, t_point map_grid_size)
{
	t_img	map;
	t_point	map_size;

	map_size.x = map_grid_size.x * MINIMAP_CELL;
	map_size.y = map_grid_size.y * MINIMAP_CELL;
	map = init_img(game->mlx_ptr, map_size.x, map_size.y);
	draw_rectangle(&map, (t_point){0, 0}, map_size, MAP_COLOR);
	draw_map_tiles(&map);
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
		game->move_keys[UP] = 0;
	if (key == XK_Down || key == XK_s)
		game->move_keys[DOWN] = 0;
	if (key == XK_a)
		game->move_keys[LEFT] = 0;
	if (key == XK_d)
		game->move_keys[RIGHT] = 0;
	if (key == XK_Left || key == XK_q)
		game->move_keys[ROT_L] = 0;
	if (key == XK_Right || key == XK_e)
		game->move_keys[ROT_R] = 0;
	return (0);
}

int	key_press(unsigned int key, t_game *game)
{
	if (key == XK_Escape)
		key_esc(game);
	if (key == XK_Up || key == XK_w)
		game->move_keys[UP] = 1;
	if (key == XK_Down || key == XK_s)
		game->move_keys[DOWN] = 1;
	if (key == XK_a)
		game->move_keys[LEFT] = 1;
	if (key == XK_d)
		game->move_keys[RIGHT] = 1;
	if (key == XK_Left || key == XK_q)
		game->move_keys[ROT_L] = 1;
	if (key == XK_Right || key == XK_e)
		game->move_keys[ROT_R] = 1;
	if (key == XK_m)
		game->map_toggle *= -1;
	return (0);
}

void	handle_rotation(t_game *game, float speed)
{
	if (game->move_keys[ROT_L])
	{
		game->player.angle -= 0.05 * speed;
		if (game->player.angle < 0)
			game->player.angle += 2 * PI;
		game->player.dx = cos(game->player.angle);
		game->player.dy = sin(game->player.angle);
	}
	if (game->move_keys[ROT_R])
	{
		game->player.angle += 0.05 * speed;
		if (game->player.angle > 2 * PI)
			game->player.angle -= 2 * PI;
		game->player.dx = cos(game->player.angle);
		game->player.dy = sin(game->player.angle);
	}
}

void	calculate_movement(t_game *game, float *move_x, float *move_y)
{
	if (game->move_keys[UP])
	{
		*move_x += game->player.dx;
		*move_y += game->player.dy;
	}
	if (game->move_keys[DOWN])
	{
		*move_x -= game->player.dx;
		*move_y -= game->player.dy;
	}
	if (game->move_keys[LEFT])
	{
		*move_x += game->player.dy;
		*move_y -= game->player.dx;
	}
	if (game->move_keys[RIGHT])
	{
		*move_x -= game->player.dy;
		*move_y += game->player.dx;
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
	float	move_x;
	float	move_y;

	move_x = 0.0;
	move_y = 0.0;
	calculate_movement(game, &move_x, &move_y);
	normalize_movement(&move_x, &move_y);
	game->player.x += move_x * speed;
	game->player.y += move_y * speed;
}

int	handle_keys(t_game *game)
{
	handle_rotation(game, ROT_SPD * (1000 / FRAME_RATE));
	handle_movement(game, MOV_SPD * (1000 / FRAME_RATE));
	return (0);
}

void	init_keys(t_game *game)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		game->move_keys[i] = 0;
		i++;
	}
	game->map_toggle = 1;
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
	static int	frame_time = 1000 / FRAME_RATE;
	static int	fps = 0;
	long		elapsed;

	gettimeofday(&game->current_frame, NULL);
	elapsed = (game->current_frame.tv_sec - game->last_frame.tv_sec) * 1000
		+ (game->current_frame.tv_usec - game->last_frame.tv_usec) / 1000;
	if (elapsed >= frame_time)
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

float	get_ray_dist(t_fpoint a, t_fpoint b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

t_ray	draw_h_rays(t_game *game, float *ray_angle)
{
	t_ray_calculation	h;
	t_ray				ray;

	ray.dist = 1000000;
	ray.pos.x = game->player.x;
	ray.pos.y = game->player.y;
	h.tan = -1 / tan(*ray_angle);
	if (*ray_angle > PI)
	{
		h.ray.y = (((int)(game->player.y) / MAP_CELL) * MAP_CELL) - 0.0001;
		h.origin.y = -MAP_CELL;
	}
	else if (*ray_angle < PI)
	{
		h.ray.y = (((int)(game->player.y) / MAP_CELL) * MAP_CELL) + 64;
		h.origin.y = MAP_CELL;
	}
	h.ray.x = (game->player.y - h.ray.y) * h.tan + game->player.x;
	h.origin.x = -h.origin.y * h.tan;
	h.dof = 0;
	if (*ray_angle == 0 || *ray_angle == PI)
	{
		h.ray.x = game->player.x;
		h.ray.y = game->player.y;
		h.dof = 8;
	}
	while (h.dof < 8)
	{
		h.map.x = (int)h.ray.x / MAP_CELL;
		h.map.y = (int)h.ray.y / MAP_CELL;
		if (h.map.y < 0 || h.map.y >= g_map_x || h.map.x < 0
			|| h.map.x >= g_map_x || g_map[h.map.y][h.map.x] == 1)
		{
			h.dof = 8;
			ray.pos = h.ray;
			ray.dist = get_ray_dist((t_fpoint){game->player.x, game->player.y}, ray.pos);
		}
		else
		{
			h.ray.x += h.origin.x;
			h.ray.y += h.origin.y;
			h.dof++;
		}
	}
	// draw_line(&game->win, (t_point){game->player.x + (int)game->map_offset.x - 1, game->player.y + (int)game->map_offset.y},
	// 	(t_point){(int)h.ray.x + (int)game->map_offset.x - 1, (int)h.ray.y + (int)game->map_offset.y}, WHITE);
	return (ray);
}

t_ray	draw_v_rays(t_game *game, float *ray_angle)
{
	t_ray_calculation	v;
	t_ray				ray;

	ray.dist = 1000000;
	ray.pos.x = game->player.x;
	ray.pos.y = game->player.y;
	v.tan = -1 * tan(*ray_angle);
	if (*ray_angle > P2 && *ray_angle < P3)
	{
		v.ray.x = (((int)(game->player.x) / MAP_CELL) * MAP_CELL) - 0.0001;
		v.origin.x = -MAP_CELL;
	}
	else if (*ray_angle < P2 || *ray_angle > P3)
	{
		v.ray.x = (((int)(game->player.x) / MAP_CELL) * MAP_CELL) + 64;
		v.origin.x = MAP_CELL;
	}
	v.ray.y = (game->player.x - v.ray.x) * v.tan + game->player.y;
	v.origin.y = -v.origin.x * v.tan;
	v.dof = 0;
	if (*ray_angle == 0 || *ray_angle == PI)
	{
		v.ray.x = game->player.x;
		v.ray.y = game->player.y;
		v.dof = 8;
	}
	while (v.dof < 8)
	{
		v.map.x = (int)v.ray.x / MAP_CELL;
		v.map.y = (int)v.ray.y / MAP_CELL;
		if (v.map.y < 0 || v.map.y >= g_map_x || v.map.x < 0
			|| v.map.x >= g_map_x || g_map[v.map.y][v.map.x] == 1)
		{
			v.dof = 8;
			ray.pos = v.ray;
			ray.dist = get_ray_dist((t_fpoint){game->player.x, game->player.y}, ray.pos);
		}
		else
		{
			v.ray.x += v.origin.x;
			v.ray.y += v.origin.y;
			v.dof++;
		}
	}
	// draw_line(&game->win, (t_point){game->player.x + (int)game->map_offset.x + 1, game->player.y + (int)game->map_offset.y},
	// 	(t_point){(int)v.ray.x + (int)game->map_offset.x + 1, (int)v.ray.y + (int)game->map_offset.y}, RED);
	return (ray);
}

void	draw_map(t_game *game)
{
	t_ray	h;
	t_ray	v;
	int		rays;
	float	ray_angle;
	float	dist;
	float	line_height;
	int		color;
	float	fov;
	float	dr;

	fov = FOV * PI / 180;
	dr = fov / RES_X;
	ray_angle = game->player.angle - (dr * (RES_X / 2));
	if (ray_angle < 0)
		ray_angle += 2 * PI;
	if (ray_angle > 2 * PI)
		ray_angle -= 2 * PI;
	put_img((t_point){0, 0}, game->bg.size, &game->bg, &game->view);
	rays = 0;
	while (rays < RES_X)
	{
		h = draw_h_rays(game, &ray_angle);
		v = draw_v_rays(game, &ray_angle);
		if (h.dist > v.dist)
		{
			draw_line(&game->win,
				(t_point){game->player.x + (int)game->map_offset.x,
				game->player.y + (int)game->map_offset.y},
				(t_point){(int)v.pos.x + (int)game->map_offset.x,
				(int)v.pos.y + (int)game->map_offset.y}, RED);
			dist = v.dist;
			color = 0x34363C;
		}
		else
		{
			draw_line(&game->win,
				(t_point){game->player.x + (int)game->map_offset.x,
				game->player.y + (int)game->map_offset.y},
				(t_point){(int)h.pos.x + (int)game->map_offset.x,
				(int)h.pos.y + (int)game->map_offset.y}, RED);
			dist = h.dist;
			color = 0x41434B;
		}
		line_height = (WALL * RES_Y) / dist;
		if (line_height > RES_Y)
			line_height = RES_Y;
		draw_line(&game->view,
			(t_point){rays, RES_Y / 2 - line_height / 2},
			(t_point){rays, RES_Y / 2 + line_height / 2}, color);
		rays++;
		ray_angle += dr;
		if (ray_angle < 0)
			ray_angle += 2 * PI;
		if (ray_angle > 2 * PI)
			ray_angle -= 2 * PI;
	}
}

void	draw_minimap(t_game *game)
{
	put_img(game->map_offset, game->map.size, &game->map, &game->win);
	draw_map_player(&game->win, game->player,
		(t_point){game->map_offset.x, game->map_offset.y});
}

void	handle_mouse(t_game *game)
{
	static t_point	center = {RES_X / 2, RES_Y / 2};
	int				delta_x;
	t_point			mouse;

	mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr, &mouse.x, &mouse.y);
	delta_x = mouse.x - center.x;
	if (delta_x != 0)
	{
		game->player.angle += delta_x * MOUSE_SEN;
		if (game->player.angle < 0)
			game->player.angle += PI2;
		else if (game->player.angle > PI2)
			game->player.angle -= PI2;
		game->player.dx = cos(game->player.angle);
		game->player.dy = sin(game->player.angle);
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, center.x, center.y);
	}
}

int	game_loop(t_game *game)
{
	handle_mouse(game);
	if (should_render_frame(game))
	{
		handle_keys(game);
		draw_map(game);
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
	t_point	pos;

	pos.x = 4;
	pos.y = 4;
	game->player.x = pos.x * MAP_CELL - 1 + (MAP_CELL / 2);
	game->player.y = pos.y * MAP_CELL - 1 + (MAP_CELL / 2);
	game->player.angle = 0;
	game->player.dx = cos(game->player.angle);
	game->player.dy = sin(game->player.angle);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (input_validation(ac, av) == -1)
		return (1);
	game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr, RES_X, RES_Y, "cub3D");
	game.win = init_img(game.mlx_ptr, RES_X, RES_Y);
	game.view = init_img(game.mlx_ptr, RES_X, RES_Y);
	game.bg = init_bg(game.mlx_ptr);
	game.map = init_map(&game, (t_point){g_map_x, g_map_y});
	game.map_offset.x = RES_X - game.map.size.x - RES_X / 50;
	game.map_offset.y = RES_X / 50;
	game.fps = NULL;
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
