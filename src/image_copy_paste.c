/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_copy_paste.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 06:34:39 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/04 23:18:02 by jaslim           ###   ########.fr       */
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
