/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:51:12 by jaslim            #+#    #+#             */
/*   Updated: 2024/08/10 14:40:15 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <math.h>

# define RES_X 1280
# define RES_Y 720
# define WALL 64

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
	t_point		size;
}				t_img;

typedef struct s_sprites
{
	t_img		wall[4];
}				t_sprites;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		mlx_win_img;
	t_sprites	sprites;
}				t_game;

#endif