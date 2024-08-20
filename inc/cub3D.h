/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:23:34 by jaslim            #+#    #+#             */
/*   Updated: 2024/08/21 00:28:35 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <sys/time.h>

# define FRAME_RATE 60

// resolution
# define RES_X 1280
# define RES_Y 720
# define WALL 64

// map
# define CELL 64
# define MAP_COLOR 0x0ADAF3

// movement
# define MOV_SPD 0.1
# define ROT_SPD 0.1
# define UP 0
# define DOWN 1
# define LEFT 2
# define RIGHT 3
# define ROT_L 4
# define ROT_R 5

// colors
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define BLACK 0x000000
# define WHITE 0xFFFFFF

// math
# define PI 3.14159265358979323846
# define P2 1.57079632679
# define P3 4.71238898038
# define FOV 1.0471975512
# define DR 0.00081812308

typedef struct s_fpoint
{
	float			x;
	float			y;
}					t_fpoint;

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_triangle
{
	t_point			origin;
	int				angle;
	int				size;
}					t_triangle;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_len;
	int				endian;
	t_point			size;
}					t_img;

typedef struct s_sprites
{
	t_img			wall[4];
}					t_sprites;

typedef struct s_player
{
	float			x;
	float			y;
	float			dx;
	float			dy;
	float			angle;
}					t_player;

typedef struct s_ray
{
	float			dist;
	t_fpoint		pos;
}					t_ray;

typedef struct s_ray_calculation
{
	int				dof;
	t_point			map;
	t_fpoint		ray;
	t_fpoint		origin;
	float			tan;
}					t_ray_calculation;

typedef struct s_game
{
	struct timeval	current_frame;
	struct timeval	last_frame;
	long			elapsed;
	void			*mlx_ptr;
	void			*win_ptr;
	int				move_keys[6];
	t_player		player;
	t_img			win;
	t_img			view;
	t_img			map;
	int				map_toggle;
	t_point			map_offset;
	t_img			bg;
	t_sprites		sprites;
}					t_game;

#endif