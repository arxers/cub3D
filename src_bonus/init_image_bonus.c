/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 06:53:25 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/05 19:44:55 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D_bonus.h"

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
	if (load_xpm(game->mlx, game->scene.no, &game->img[T_NORTH])
		|| load_xpm(game->mlx, game->scene.so, &game->img[T_SOUTH])
		|| load_xpm(game->mlx, game->scene.ea, &game->img[T_EAST])
		|| load_xpm(game->mlx, game->scene.we, &game->img[T_WEST])
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
