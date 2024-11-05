/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 06:54:53 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/05 18:23:37 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	put_img(t_vec offset, t_img *src, t_img *dst)
{
	t_vec	src_pos;
	t_vec	dst_pos;

	src_pos.y = 0;
	while (src_pos.y < src->size.y)
	{
		src_pos.x = 0;
		while (src_pos.x < src->size.x)
		{
			dst_pos.x = src_pos.x + offset.x;
			dst_pos.y = src_pos.y + offset.y;
			if (dst_pos.x >= 0 && dst_pos.x < dst->size.x
				&& dst_pos.y >= 0 && dst_pos.y < dst->size.y)
				set_pixel_alpha(dst, dst_pos.x, dst_pos.y,
					get_pixel(src, src_pos.x, src_pos.y));
			src_pos.x++;
		}
		src_pos.y++;
	}
}

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
