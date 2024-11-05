/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 06:34:40 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/04 23:29:40 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	ft_destroy_image(void *mlx_ptr, t_img *img)
{
	if (mlx_ptr && img->img)
		mlx_destroy_image(mlx_ptr, img->img);
	img->img = NULL;
}

void	free_int_array(int	**output, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_free_void((void **)&output[i]);
		i++;
	}
	free(output);
}

int	cleanup(t_game *game, unsigned char status, char *msg)
{
	int	i;

	mlx_do_key_autorepeaton(game->mlx);
	i = 0;
	while (i < IMG_MAX)
	{
		ft_destroy_image(game->mlx, &game->img[i]);
		i++;
	}
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	game->win = NULL;
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	ft_free_void(&game->mlx);
	ft_free(&game->frame.fps_str);
	free_int_array(game->map.arr, game->map.size.y);
	if (msg)
		ft_putstr_fd(msg, 2);
	exit(status);
}

void	error_handler(t_game *game, int status)
{
	if (status == 1)
		cleanup(game, 1, "Error\nFailed to initialize game\n");
	else if (status == 2)
		cleanup(game, 1, "Error\nError: Failed to create image\n");
	else if (status == 3)
		cleanup(game, 1, "Error\nError: Missing texture file/files\n");
}
