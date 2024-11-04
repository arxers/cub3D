/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 06:54:53 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/04 23:18:44 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	draw_diagonal_lines(t_img *img, t_vec size, unsigned int color)
{
	t_vec	start;
	t_vec	end;
	int		i;
	int		step;

	step = 16;
	i = -size.x;
	while (i < size.x * 2)
	{
		start = (t_vec){i, -1};
		end = (t_vec){i + size.x, size.y - 1};
		draw_line(img, start, end, color);
		i += step;
	}
}

// Fill an img with a specified color in hexadecimal format.
void	fill_img(t_img *img, unsigned int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->size.y)
	{
		x = 0;
		while (x < img->size.x)
		{
			set_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}
