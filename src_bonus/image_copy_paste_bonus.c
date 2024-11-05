/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_copy_paste_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 06:34:39 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/05 19:45:08 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D_bonus.h"

void	put_img_scale_darken(t_vec ofs, t_img *src, t_img *dst,
	t_fvec scale)
{
	t_fvec	sp;
	t_vec	dp;
	t_vec	s_mid;

	scale.x = 1.0 / scale.x;
	scale.y = 1.0 / scale.y;
	s_mid.x = src->size.x * 0.5;
	s_mid.y = src->size.y * 0.5;
	dp.y = 0;
	while (dp.y < dst->size.y)
	{
		dp.x = 0;
		while (dp.x < dst->size.x)
		{
			sp.x = (dp.x - ofs.x - dst->size.x * 0.5) * scale.x + s_mid.x;
			sp.y = (dp.y - ofs.y - dst->size.y * 0.5) * scale.y + s_mid.y;
			if (sp.x >= 0 && sp.x < src->size.x
				&& sp.y >= 0 && sp.y < src->size.y)
				set_pixel_alpha(dst, dp.x, dp.y,
					darken(get_pixel(src, sp.x, sp.y), src->intensity));
			dp.x++;
		}
		dp.y++;
	}
}

void	put_img_scale_mid_bot(t_vec ofs, t_img *src, t_img *dst,
	t_fvec scale)
{
	t_fvec	sp;
	t_vec	dp;
	t_vec	s_mid;

	scale.x = 1.0 / scale.x;
	scale.y = 1.0 / scale.y;
	s_mid.x = src->size.x * 0.5;
	s_mid.y = -src->size.x;
	dp.y = 0;
	while (dp.y < dst->size.y)
	{
		dp.x = 0;
		while (dp.x < dst->size.x)
		{
			sp.x = (dp.x - ofs.x - dst->size.x * 0.5) * scale.x + s_mid.x;
			sp.y = (dp.y - ofs.y - dst->size.y * 0.5) * scale.y + s_mid.y;
			if (sp.x >= 0 && sp.x < src->size.x
				&& sp.y >= 0 && sp.y < src->size.y)
				set_pixel_alpha(dst, dp.x, dp.y,
					get_pixel(src, sp.x, sp.y));
			dp.x++;
		}
		dp.y++;
	}
}

void	put_img_scale_mid(t_vec ofs, t_img *src, t_img *dst, t_fvec scale)
{
	t_fvec	sp;
	t_vec	dp;
	t_vec	s_mid;

	scale.x = 1.0 / scale.x;
	scale.y = 1.0 / scale.y;
	s_mid.x = src->size.x * 0.5;
	s_mid.y = src->size.y * 0.5;
	dp.y = 0;
	while (dp.y < dst->size.y)
	{
		dp.x = 0;
		while (dp.x < dst->size.x)
		{
			sp.x = (dp.x - ofs.x - dst->size.x * 0.5) * scale.x + s_mid.x;
			sp.y = (dp.y - ofs.y - dst->size.y * 0.5) * scale.y + s_mid.y;
			if (sp.x >= 0 && sp.x < src->size.x
				&& sp.y >= 0 && sp.y < src->size.y)
				set_pixel_alpha(dst, dp.x, dp.y,
					get_pixel(src, sp.x, sp.y));
			dp.x++;
		}
		dp.y++;
	}
}

void	put_img_scale(t_vec offset, t_img *src, t_img *dst, t_fvec scale)
{
	t_fvec	src_pos;
	t_vec	dst_pos;

	scale.x = 1.0 / scale.x;
	scale.y = 1.0 / scale.y;
	dst_pos.y = 0;
	while (dst_pos.y < dst->size.y)
	{
		dst_pos.x = 0;
		while (dst_pos.x < dst->size.x)
		{
			src_pos.x = (dst_pos.x - offset.x) * scale.x;
			src_pos.y = (dst_pos.y - offset.y) * scale.y;
			if (src_pos.x >= 0 && src_pos.x < src->size.x
				&& src_pos.y >= 0 && src_pos.y < src->size.y)
				set_pixel_alpha(dst, dst_pos.x, dst_pos.y,
					get_pixel(src, src_pos.x, src_pos.y));
			dst_pos.x++;
		}
		dst_pos.y++;
	}
}

// Draw an img to another img by rewriting parts the src addr with dst addr.
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
