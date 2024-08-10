/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:44:00 by jaslim            #+#    #+#             */
/*   Updated: 2024/08/10 14:42:24 by jaslim           ###   ########.fr       */
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

void	img_to_img(t_point offset, t_point size, t_img *src, t_img *dst)
{
	int		x;
	int		y;
	y = 0;
	if (offset.x < 0 || offset.y < 0
		|| (offset.x + size.x) > (dst->line_len / (dst->bits_per_pixel / 8))
		|| (offset.y + size.y) > (dst->line_len / (dst->bits_per_pixel / 8)))
        return;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			set_pixel(dst, x + offset.x, y + offset.y, get_pixel(src, x, y));
			x++;
		}
		y++;
	}
}

void	transparency_test(t_game *cub3d)
{
	t_img	test_alpha;
	t_point size;

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

int	main(int ac, char **av)
{
	t_game	cub3d;

	if (input_validation(ac, av) == -1)
		return (1);
	cub3d.mlx_ptr = mlx_init();
	cub3d.win_ptr = mlx_new_window(cub3d.mlx_ptr, RES_X, RES_Y, "cub3D");
	cub3d.mlx_win_img.img = mlx_new_image(cub3d.mlx_ptr, RES_X, RES_Y);
	cub3d.mlx_win_img.addr = mlx_get_data_addr(cub3d.mlx_win_img.img, &cub3d.mlx_win_img.bits_per_pixel,
			&cub3d.mlx_win_img.line_len, &cub3d.mlx_win_img.endian);
	// ft_pixel_put(&cub3d.img, 5, 5, 0x00FF00);
	// ft_pixel_put(&cub3d.img, 10, 10, 0x00FF00);
	// for (int i = 0; i < 500; i += 10)
	load_xpms(&cub3d);
	draw_circle(&cub3d.mlx_win_img, (t_point){.x = (RES_X / 2), .y = (RES_Y / 2)}, 400, 0x00FF00);
	// transparency_test(&cub3d);
	mlx_put_image_to_window(cub3d.mlx_ptr, cub3d.win_ptr, cub3d.mlx_win_img.img, 0, 0);
	// cleanup(&cub3d);
	mlx_loop(cub3d.mlx_ptr);
	(void)av;
	return (0);
}
