/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:44:00 by jaslim            #+#    #+#             */
/*   Updated: 2024/08/19 10:14:29 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	g_map_x = 10;
int	g_map_y = 10;
int	g_map[10][10] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,1,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,0,0,0,0,0,1},
	{1,0,1,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
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

void	img_to_img(t_point origin, t_point size, t_img *src, t_img *dst)
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
	img_to_img((t_point){RES_X / 2 - (game->sprites.wall[0].size.x / 2), RES_Y / 2 - (game->sprites.wall[0].size.y / 2)}, game->sprites.wall[0].size, &game->sprites.wall[0], &game->mlx_win_img);
	return (0);
}

void	draw_rectangle(t_img *dst, t_point origin, t_point size, unsigned int color)
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

void	draw_circle_outline(t_img *img, t_point origin, int radius, unsigned int color)
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
	while (start.x != end.x || start.y != end.y)
	{
		brasenham(&err, &start, d, s);
		set_pixel(img, start.x, start.y, color);
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

void	draw_map_player(t_img *img, t_player p)
{
	float		d;
	float		r;
	t_point		pointer;

	draw_circle(img, (t_point){(int)p.x, (int)p.y}, CELL / 4, WHITE);
	d = CELL / 3;
	r = CELL / 8;
	pointer.x = (int)(p.x + p.dx * d);
	pointer.y = (int)(p.y + p.dy * d);
	draw_circle(img, pointer, r, WHITE);
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
	mlx_destroy_image(game->mlx_ptr, game->mlx_win_img.img);
	mlx_destroy_image(game->mlx_ptr, game->map.img);
	mlx_destroy_image(game->mlx_ptr, game->bg.img);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
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
	draw_rectangle(&bg, (t_point){0, RES_Y / 2}, size, 0x404856);
	return (bg);
}

void	draw_map_tiles(t_img *map)
{
	t_point	count;
	t_point	origin;
	t_point	size;

	count.y = 0;
	origin.y = 0;
	size.x = CELL;
	size.y = CELL;
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
			origin.x += CELL + 1;
		}
		count.y++;
		origin.y += CELL + 1;
	}
}

t_img	init_map(t_game *game, t_point map_grid_size)
{
	t_img	map;
	t_point	map_size;

	map_size.x = (map_grid_size.x * (CELL + 1)) - 1;
	map_size.y = (map_grid_size.y * (CELL + 1)) - 1;
	map = init_img(game->mlx_ptr, map_size.x, map_size.y);
	draw_rectangle(&map, (t_point){0, 0}, map_size, MAP_COLOR);
	draw_map_tiles(&map);
	return (map);
}

int	key_esc(t_game *game)
{
	cleanup(game);
	ft_printf("exit\n");
	exit(0);
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
	return (0);
}

void	handle_rotation(t_game *game, float speed)
{
	if (game->move_keys[ROT_L])
	{
		game->player.angle -= 0.1 * speed;
		if (game->player.angle < 0)
			game->player.angle += 2 * PI;
		game->player.dx = cos(game->player.angle);
		game->player.dy = sin(game->player.angle);
	}
	if (game->move_keys[ROT_R])
	{
		game->player.angle += 0.1 * speed;
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
	while (i < 6)
	{
		game->move_keys[i] = 0;
		i++;
	}
}

int	should_render_frame(t_game *game)
{
	static int	frame_time = 1000 / FRAME_RATE;
	long		elapsed;

	gettimeofday(&game->current_frame, NULL);
	elapsed = (game->current_frame.tv_sec - game->last_frame.tv_sec) * 1000
		+ (game->current_frame.tv_usec - game->last_frame.tv_usec) / 1000;
	if (elapsed >= frame_time)
	{
		game->last_frame = game->current_frame;
		return (1);
	}
	return (0);
}

int	render_frame(t_game *game)
{
	if (should_render_frame(game))
	{
		handle_keys(game);
		img_to_img((t_point){0, 0}, (t_point){RES_X, RES_Y}, &game->bg, &game->mlx_win_img);
		img_to_img((t_point){RES_X - game->map.size.x, 0}, game->map.size, &game->map, &game->mlx_win_img);
		draw_map_player(&game->mlx_win_img, game->player);
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->mlx_win_img.img, 0, 0);
	}
	return (0);
}

void	init_player_pos(t_game *game)
{
	game->player.x = RES_X / 2;
	game->player.y = RES_Y / 2;
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
	game.mlx_win_img = init_img(game.mlx_ptr, RES_X, RES_Y);
	game.bg = init_bg(game.mlx_ptr);
	game.map = init_map(&game, (t_point){g_map_x, g_map_y});
	init_keys(&game);
	init_player_pos(&game);
	gettimeofday(&game.last_frame, NULL);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, &key_press, &game);
	mlx_hook(game.win_ptr, KeyRelease, KeyReleaseMask, &key_release, &game);
	mlx_hook(game.win_ptr, DestroyNotify, StructureNotifyMask, &key_esc, NULL);
	mlx_loop_hook(game.mlx_ptr, &render_frame, &game);
	mlx_loop(game.mlx_ptr);
	(void)av;
	return (0);
}
