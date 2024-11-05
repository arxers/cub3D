/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_pixel_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 06:34:38 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/05 19:45:06 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D_bonus.h"

// Sets a pixel in the img address to a specified color in hexadecimal format.
void	set_pixel(t_img *img, int x, int y, unsigned int color)
{
	const int	step = (img->bits_per_pixel / 8);
	char		*dst;

	if (x < 0 || y < 0 || x >= img->size.x || y >= img->size.y)
		return ;
	dst = img->addr + ((y * img->line_len) + x * step);
	*(unsigned int *)dst = color;
}

// Sets a pixel in the img address to a specified color in hexadecimal format.
// Ignores transparent pixels, as well as MAGENTA (0xFF00FF).
void	set_pixel_alpha(t_img *img, int x, int y, unsigned int color)
{
	const int	step = (img->bits_per_pixel / 8);
	char		*dst;

	if (x < 0 || y < 0 || x >= img->size.x || y >= img->size.y
		|| (color >> 24) & 0xFF || color == MAGENTA)
		return ;
	dst = img->addr + ((y * img->line_len) + x * step);
	*(unsigned int *)dst = color;
}

// Returns a pixel's color in the img address.
unsigned int	get_pixel(t_img *img, int x, int y)
{
	const int	step = (img->bits_per_pixel / 8);
	char		*src;

	src = img->addr + ((y * img->line_len) + x * step);
	return (*(unsigned int *)src);
}
