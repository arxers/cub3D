/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:23:34 by jaslim            #+#    #+#             */
/*   Updated: 2024/08/13 18:47:28 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>

// resolution
# define RES_X 1280
# define RES_Y 720
# define WALL 64

// map
# define CELL 16
# define MAP_COLOR 0x0ADAF3

// movement
# define MOV_SPD 0.2
# define UP 0
# define DOWN 1
# define LEFT 2
# define RIGHT 3

// colors
# define BLACK 0x000000
# define WHITE 0xFFFFFF

# define PI 3.14159265358979323846

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

typedef struct s_player
{
	float		x;
	float		y;
	float		dx;
	float		dy;
	float		angle;
}				t_player;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			move_keys[4];
	t_player	player;
	t_img		mlx_win_img;
	t_img		map;
	t_img		bg;
	t_sprites	sprites;
}				t_game;

#endif