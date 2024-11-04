/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 06:54:53 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/04 08:07:10 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

// Darkens a color in hexadecimal format, by a specified factor. (1.0 to 0.0)
// The closer the factor is to 0, the closer to black it becomes.
unsigned int	darken(unsigned int color, float factor)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if ((color >> 24) & 0xFF)
		return (color);
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = (color >> 0) & 0xFF;
	r *= factor;
	g *= factor;
	b *= factor;
	return ((r << 16) | (g << 8) | b);
}

// Used in conjunction with darken() to set light intensity.
float	set_intensity(t_light light, float dist)
{
	const float	inverse_range = 1.0 / (light.max - light.min);
	float		intensity;

	intensity = (light.max - dist) * inverse_range;
	if (intensity < 0)
		intensity = 0;
	if (intensity > 1)
		intensity = 1;
	intensity = intensity * (1 - light.ambient) + light.ambient;
	return (intensity);
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
