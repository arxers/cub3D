/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:44:00 by jaslim            #+#    #+#             */
/*   Updated: 2024/08/12 23:12:45 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	map[10][10] =
{
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};

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
        return;
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

void	transparency_test(t_game *cub3d)
{
	t_img	test_alpha;
	t_point	size;

	test_alpha.img = mlx_xpm_file_to_image(cub3d->mlx_ptr, "textures/alpha_test.xpm", &size.x, &size.y);
	test_alpha.addr = mlx_get_data_addr(test_alpha.img, &test_alpha.bits_per_pixel,
			&test_alpha.line_len, &test_alpha.endian);
	img_to_img((t_point){RES_X / 2 - (size.x / 2), RES_Y / 2 - (size.y / 2)}, size, &test_alpha, &cub3d->mlx_win_img);
}

int	load_xpm(void *mlx, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(mlx, path, &img->size.x, &img->size.y);
	if (!img->img)
		return (-1);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_len, &img->endian);
	return (0);
}

int	load_xpms(t_game *cub3d)
{
	if (load_xpm(cub3d->mlx_ptr, "textures/wall/wall1.xpm", &cub3d->sprites.wall[0]) == -1)
		return (-1);
	img_to_img((t_point){RES_X / 2 - (cub3d->sprites.wall[0].size.x / 2), RES_Y / 2 - (cub3d->sprites.wall[0].size.y / 2)}, cub3d->sprites.wall[0].size, &cub3d->sprites.wall[0], &cub3d->mlx_win_img);
	return (0);
}

void	draw_rectangle(t_img *img, t_point origin, t_point size, unsigned int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			set_pixel(img, x + origin.x, y + origin.y, color);
			x++;
		}
		y++;
	}
}

void	draw_filled_circle(t_img *img, t_point origin, int radius, unsigned int color)
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
				set_pixel(img, p.x, p.y, color);
			p.x++;
		}
		p.y++;
	}
}

void	draw_circle(t_img *img, t_point origin, int radius, unsigned int color)
{
	int		x;
	int		y;
	float	angle;

	angle = 0;
	while (angle < 360)
	{
		x = origin.x + radius * cos(angle * M_PI / 180);
		y = origin.y + radius * sin(angle * M_PI / 180);
		set_pixel(img, x, y, color);
		angle += 0.1;
	}
}
void	draw_player(t_img *img, t_player p)
{
	draw_filled_circle(img, (t_point){(int)p.px, (int)p.py}, 10, 0xFFFFFF);
	draw_filled_circle(img, (t_point){(int)p.px - 20, (int)p.py}, 10, 0xFFFFFF);
	draw_filled_circle(img, (t_point){(int)p.px - 10, (int)p.py - 10}, 10, 0xFFFFFF);
	draw_filled_circle(img, (t_point){(int)p.px - 10, (int)p.py - 20}, 10, 0xFFFFFF);
	draw_filled_circle(img, (t_point){(int)p.px - 10, (int)p.py - 30}, 10, 0xFFFFFF);
	draw_filled_circle(img, (t_point){(int)p.px - 10, (int)p.py - 40}, 10, 0xFFFFFF);
	draw_filled_circle(img, (t_point){(int)p.px - 10, (int)p.py - 50}, 11, 0xFFFFFF);
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

int	cleanup(t_game *cub3d)
{
	mlx_destroy_image(cub3d->mlx_ptr, cub3d->sprites.wall[0].img);
	mlx_destroy_image(cub3d->mlx_ptr, cub3d->mlx_win_img.img);
	mlx_destroy_window(cub3d->mlx_ptr, cub3d->win_ptr);
	mlx_destroy_display(cub3d->mlx_ptr);
	free(cub3d->mlx_ptr);
	exit(0);
}

t_point	center(t_point origin, t_point size)
{
	origin.x -= size.x / 2;
	origin.y -= size.y / 2;
	return (origin);
}

t_img	create_bg(void *mlx_ptr)
{
	t_img	bg;

	bg.img = mlx_new_image(mlx_ptr, RES_X, RES_Y);
	bg.addr = mlx_get_data_addr(bg.img, &bg.bits_per_pixel, &bg.line_len, &bg.endian);
	draw_rectangle(&bg, (t_point){0, 0}, (t_point){RES_X, RES_Y / 2}, 0x171B22);
	draw_rectangle(&bg, (t_point){0, RES_Y / 2}, (t_point){RES_X, RES_Y / 2}, 0x404856);
	return (bg);
}

int	handle_esc(void)
{
	ft_printf("exit\n");
	exit(0);
	return (0);
}

int	key_release(unsigned int key, t_game *game)
{
	if (key == XK_Up)
		game->arrow_keys[0] = 0;
	if (key == XK_Left)
		game->arrow_keys[1] = 0;
	if (key == XK_Down)
		game->arrow_keys[2] = 0;
	if (key == XK_Right)
		game->arrow_keys[3] = 0;
	return (0);
}

int	key_press(unsigned int key, t_game *game)
{
	if (key == XK_Escape)
		handle_esc();
	if (key == XK_Up)
		game->arrow_keys[0] = 1;
	if (key == XK_Left)
		game->arrow_keys[1] = 1;
	if (key == XK_Down)
		game->arrow_keys[2] = 1;
	if (key == XK_Right)
		game->arrow_keys[3] = 1;
	return (0);
}

int	handle_keys(t_game *game)
{
	if (game->arrow_keys[0])
	{
		game->player.py--;
		ft_printf("up\n");
	}
	if (game->arrow_keys[1])
	{
		game->player.px--;
		ft_printf("left\n");
	}
	if (game->arrow_keys[2])
	{
		game->player.py++;
		ft_printf("down\n");
	}
	if (game->arrow_keys[3])
	{
		game->player.px++;
		ft_printf("right\n");
	}
	return (0);
}

void	init_keys(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->arrow_keys[i] = 0;
		i++;
	}
}

int	render_frame(t_game *game)
{
	handle_keys(game);
	img_to_img((t_point){0, 0}, (t_point){RES_X, RES_Y}, &game->bg, &game->mlx_win_img);
	draw_player(&game->mlx_win_img, game->player);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->mlx_win_img.img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (input_validation(ac, av) == -1)
		return (1);
	game.mlx_ptr = mlx_init();
	game.win_ptr = mlx_new_window(game.mlx_ptr, RES_X, RES_Y, "cub3D");
	game.mlx_win_img.img = mlx_new_image(game.mlx_ptr, RES_X, RES_Y);
	game.mlx_win_img.addr = mlx_get_data_addr(game.mlx_win_img.img, &game.mlx_win_img.bits_per_pixel,
			&game.mlx_win_img.line_len, &game.mlx_win_img.endian);
	game.bg = create_bg(game.mlx_ptr);
	
	// draw_filled_circle(&game.mlx_win_img, (t_point){RES_X / 2, RES_Y / 2}, 50, 0xFF00FF);
	// draw_filled_circle(&game.mlx_win_img, (t_point){RES_X / 2, RES_Y / 2}, 300, 0xFF00FF);
	// transparency_test(&game);
	
	// cleanup(&cub3d);

	init_keys(&game);
	game.player.px = 0;
	game.player.py = 0;
	
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, &key_press, &game);
	mlx_hook(game.win_ptr, KeyRelease, KeyReleaseMask, &key_release, &game);
	mlx_hook(game.win_ptr, DestroyNotify, StructureNotifyMask, &handle_esc, NULL);
	mlx_loop_hook(game.mlx_ptr, &render_frame, &game);
	mlx_loop(game.mlx_ptr);
	(void)av;
	return (0);
}
