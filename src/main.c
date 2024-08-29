/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:44:00 by jaslim            #+#    #+#             */
/*   Updated: 2024/08/28 21:09:07 by jaslim           ###   ########.fr       */
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
	static float	scale = (float)MINIMAP_CELL;
	t_point			player_pos;
	t_point			pointer_pos;
	float			pointer_radius;
	float			pointer_dist;

	player_pos.x = (int)((p.pos.x * scale) + origin.x);
	player_pos.y = (int)((p.pos.y * scale) + origin.y);
	draw_circle(img, player_pos, MINIMAP_CELL * 0.25, WHITE);
	pointer_radius = MINIMAP_CELL * 0.15;
	pointer_dist = 0.25;
	pointer_pos.x = (int)((p.pos.x + (p.dir.x * pointer_dist)) * scale) + origin.x;
	pointer_pos.y = (int)((p.pos.y + (p.dir.y * pointer_dist)) * scale) + origin.y;
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

void	handle_rotation(t_game *game)
{
	// t_fpoint	old_dir;
	// t_fpoint	old_plane;

	// old_dir = game->player.dir;
	// old_plane = game->player.plane;
	// printf("dir.x: %f, dir.y: %f\n", game->player.dir.x, game->player.dir.y);
	if (game->move_keys[ROT_R])
	{
      float oldDirX = game->player.dir.x;
      game->player.dir.x = game->player.dir.x * cos(-ROT_SPD) - game->player.dir.y * sin(-ROT_SPD);
      game->player.dir.y = oldDirX * sin(-ROT_SPD) + game->player.dir.y * cos(-ROT_SPD);
      float oldPlaneX = game->player.plane.x;
      game->player.plane.x = game->player.plane.x * cos(-ROT_SPD) - game->player.plane.y * sin(-ROT_SPD);
      game->player.plane.y = oldPlaneX * sin(-ROT_SPD) + game->player.plane.y * cos(-ROT_SPD);
	}
	if (game->move_keys[ROT_L])
	{
      float oldDirX = game->player.dir.x;
      game->player.dir.x = game->player.dir.x * cos(ROT_SPD) - game->player.dir.y * sin(ROT_SPD);
      game->player.dir.y = oldDirX * sin(ROT_SPD) + game->player.dir.y * cos(ROT_SPD);
      float oldPlaneX = game->player.plane.x;
      game->player.plane.x = game->player.plane.x * cos(ROT_SPD) - game->player.plane.y * sin(ROT_SPD);
      game->player.plane.y = oldPlaneX * sin(ROT_SPD) + game->player.plane.y * cos(ROT_SPD);
	}
}

// void	handle_rotation(t_game *game, float speed)
// {
// 	if (game->move_keys[ROT_L])
// 	{
// 		game->player.angle -= 0.05 * speed;
// 		if (game->player.angle < 0)
// 			game->player.angle += 2 * PI;
// 		game->player.dir.x = cos(game->player.angle);
// 		game->player.dir.y = sin(game->player.angle);
// 	}
// 	if (game->move_keys[ROT_R])
// 	{
// 		game->player.angle += 0.05 * speed;
// 		if (game->player.angle > 2 * PI)
// 			game->player.angle -= 2 * PI;
// 		game->player.dir.x = cos(game->player.angle);
// 		game->player.dir.y = sin(game->player.angle);
// 	}
// }

void	calculate_movement(t_game *game, float *move_x, float *move_y)
{
	if (game->move_keys[UP])
	{
		*move_x += game->player.dir.x;
		*move_y += game->player.dir.y;
	}
	if (game->move_keys[DOWN])
	{
		*move_x -= game->player.dir.x;
		*move_y -= game->player.dir.y;
	}
	if (game->move_keys[LEFT])
	{
		*move_x += game->player.dir.y;
		*move_y -= game->player.dir.x;
	}
	if (game->move_keys[RIGHT])
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
	float	move_x;
	float	move_y;

	move_x = 0.0;
	move_y = 0.0;
	calculate_movement(game, &move_x, &move_y);
	normalize_movement(&move_x, &move_y);
	game->player.pos.x += move_x * speed;
	game->player.pos.y += move_y * speed;
}

int	handle_keys(t_game *game)
{
	handle_rotation(game/* , ROT_SPD * (1000 / FRAME_RATE) */);
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

void	draw_minimap(t_game *game)
{
	put_img(game->map_offset, game->map.size, &game->map, &game->win);
	draw_map_player(&game->win, game->player,
		(t_point){game->map_offset.x, game->map_offset.y});
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
			delta_dist.x = 1e30;
		else
			delta_dist.x = fabsf(1 / ray_dir.x);
		if (ray_dir.y == 0)
			delta_dist.y = 1e30;
		else
			delta_dist.y = fabsf(1 / ray_dir.y);
		hit = 0;
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
			draw_start = 0;
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
}

int	game_loop(t_game *game)
{
	// handle_mouse(game);
	if (should_render_frame(game))
	{
		handle_keys(game);
		put_img((t_point){0, 0}, game->bg.size, &game->bg, &game->view);
		lodev(game);
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
	game->player.dir.x = -1;
	game->player.dir.y = 0;
	game->player.plane.x = 0;
	game->player.plane.y = 0.66;
	printf("player dir x:%f\n", game->player.dir.x);
	printf("player dir y:%f\n", game->player.dir.y);
	printf("player plane x:%f\n", game->player.plane.x);
	printf("player plane y:%f\n", game->player.plane.y);
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
