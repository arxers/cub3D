/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:23:34 by jaslim            #+#    #+#             */
/*   Updated: 2024/09/09 21:06:35 by jaslim           ###   ########.fr       */
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

// raycasting
# define VERTICAL 0
# define HORIZONTAL 1

// resolution
# define RES_X 1024
# define RES_Y 768
# define WALL 64

// map
# define MAP_CELL_SIZE 16
# define MAP_COLOR 0x0ADAF3

// movement multipliers
# define MOUSE_SEN 0.0025
# define MOV_SPD 0.001
# define ROT_SPD 0.0025
# define RUN_SPD 2

// colors
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define BLACK 0x000000
# define WHITE 0xFFFFFF

// math
# define PI 3.14159265358

typedef enum e_keystate
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ROT_U,
	ROT_D,
	ROT_L,
	ROT_R,
	MAP,
	MOUSE,
	RUN,
	CROUCH,
	JUMP,
	PAUSE
}					t_keystate;

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

typedef struct s_images
{
	t_img			wall[4];
	t_img			misc[32];
	t_img			win;
	t_img			view;
	t_img			map;
	t_img			map_mask;
	t_img			map_bg;
	t_img			ceiling;
	t_img			floor;
}					t_images;

typedef struct s_player
{
	t_fpoint		pos;
	t_fpoint		plane;
	t_fpoint		dir;
	float			zoom;
	float			height;
	int				pitch;
}					t_player;

typedef struct s_frame_data
{
	struct timeval	current;
	struct timeval	last;
	long			elapsed;
	float			time;
	unsigned int	fps_target;
	char			*fps_str;
}					t_frame_data;

typedef struct s_map
{
	int				*grid;
	t_point			size;
	t_point			offset;
}					t_map;

typedef struct s_game
{
	char			keys[32];
	t_images		img;
	t_frame_data	frame;
	void			*mlx_ptr;
	void			*win_ptr;
	t_player		player;
	t_map			map;
}					t_game;

#endif