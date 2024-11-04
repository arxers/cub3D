/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 06:53:25 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/04 23:24:55 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

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

int	load_xpms(t_game *game)
{
	if (load_xpm(game->mlx, game->scene.no, &game->img[T_NORTH])
		|| load_xpm(game->mlx, game->scene.so, &game->img[T_SOUTH])
		|| load_xpm(game->mlx, game->scene.ea, &game->img[T_EAST])
		|| load_xpm(game->mlx, game->scene.we, &game->img[T_WEST])
		|| load_xpm(game->mlx, "textures/shift_tab.xpm", &game->img[T_PAUSE]))
		return (-1);
	return (0);
}
