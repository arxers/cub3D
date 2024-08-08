/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:44:00 by jaslim            #+#    #+#             */
/*   Updated: 2024/08/09 00:59:08 by jaslim           ###   ########.fr       */
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

void	ft_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > RES_X || y > RES_Y)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_circle(t_img *img, t_point origin, int radius, int color)
{
	int		x;
	int		y;
	float	angle;

	angle = 0;
	while (angle < 360)
	{
		x = origin.x + radius * cos(angle * M_PI / 180);
		y = origin.y + radius * sin(angle * M_PI / 180);
		ft_pixel_put(img, x, y, color);
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

int	main(int ac, char **av)
{
	t_mlx	cub3d;

	if (input_validation(ac, av) == -1)
		return (1);
	cub3d.mlx = mlx_init();
	cub3d.mlx_win = mlx_new_window(cub3d.mlx, RES_X, RES_Y, "cub3D");
	cub3d.img.img = mlx_new_image(cub3d.mlx, RES_X, RES_Y);
	cub3d.img.addr = mlx_get_data_addr(cub3d.img.img, &cub3d.img.bits_per_pixel,
			&cub3d.img.line_len, &cub3d.img.endian);
	// ft_pixel_put(&cub3d.img, 5, 5, 0x00FF00);
	// ft_pixel_put(&cub3d.img, 10, 10, 0x00FF00);
	draw_circle(&cub3d.img, (t_point){.x = (RES_X / 2), .y = (RES_Y / 2)}, 100, 0xFF00FF);
	mlx_put_image_to_window(cub3d.mlx, cub3d.mlx_win, cub3d.img.img, 0, 0);
	mlx_loop(cub3d.mlx);
	(void)av;
	return (0);
}
