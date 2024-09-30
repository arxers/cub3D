/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:23:34 by jaslim            #+#    #+#             */
/*   Updated: 2024/09/30 20:08:46 by jaslim           ###   ########.fr       */
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
# define MAP_CELL_SIZE 24
# define MAP_COLOR 0x0ADAF3

// movement multipliers
# define MOUSE_SEN 0.0025
# define ROT_SPD 0.0025
# define RUN_SPD 2
# define PLAYER_SPD 0.002
# define ENEMY_SPD 0.0035
# define PLAYER_RADIUS 0.20
# define ENEMY_RADIUS 0.00

// colors
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define MAGENTA 0xFF00FF

// bounds
# define P_MAX_HEIGHT 0.4
# define P_MIN_HEIGHT -0.2

typedef enum e_texture
{
	T_WIN,
	T_MAP,
	T_MAP_ENEMY_PATH,
	T_MAP_TILES,
	T_MAP_MASK,
	T_MAP_BG,
	T_CEILING,
	T_FLOOR,
	T_NORTH,
	T_SOUTH,
	T_EAST,
	T_WEST,
	T_DOOR_OPEN,
	T_DOOR_CLOSE,
	T_PAUSE,
	T_DITHER,
	T_XENO0,
	T_XENO1,
	T_XENO2,
	T_XENO3,
	T_XENO4,
	T_XENO5,
	T_XENO6,
	T_XENO7,
	T_XENO_END,
	T_ITEM
}					t_texture;

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
	MAP_DISABLE,
	MAP_BIG,
	MOUSE,
	RUN,
	CROUCH,
	JUMP,
	PAUSE,
	SHOW_ENEMY_PATH
}					t_keystate;

typedef enum e_direction
{
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT,
}					t_direction;

typedef enum e_timer
{
	MS100,
	MS1000,
	TIMER_ENEMY,
	TIMER_ENEMY_MAP,
	TIMER_ENEMY_PATH,
}					t_timer;

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

typedef struct s_img
{
	void			*img;
	char			*addr;
	t_point			size;
	int				bits_per_pixel;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_item
{
	t_fpoint		pos;
	int				collected;
}					t_item;

typedef struct s_player
{
	t_fpoint		pos;
	t_fpoint		plane;
	t_fpoint		dir;
	float			z;
	float			zoom;
	int				pitch;
}					t_player;

typedef struct s_enemy
{
	t_fpoint		pos;
	t_fpoint		dist;
	t_fpoint		memory;
	t_fpoint		last_dist;
	t_fpoint		last_seen;
	t_img			img;
	int				frame;
	int				eyes;
	int				move_seed;
	int				move_inc;
}					t_enemy;

typedef struct s_frame_data
{
	struct timeval	current;
	struct timeval	last;
	char			*fps_str;
	long			elapsed;
	float			time;
	unsigned int	fps_target;
	int				fps;
}					t_frame_data;

typedef struct s_map
{
	int				**grid;
	t_point			size;
	t_point			offset;
	int				enemy_toggle;
	int				update;
}					t_map;

typedef struct s_light
{
	float			ambient;
	float			min;
	float			max;
}					t_light;

typedef struct s_ray
{
	double			line_height;
	t_fpoint		map;
	t_fpoint		dir;
	t_fpoint		side_dist;
	t_fpoint		delta_dist;
	t_point			pix;
	t_point			step;
	float			wall_dist;
	int				side;
	int				draw_start;
	int				draw_end;
}					t_ray;

typedef struct s_texture_map
{
	t_img			*wall_tex;
	t_point			coords;
	t_fpoint		hit;
	float			tex_step;
}					t_texture_map;

typedef struct s_game
{
	char			keys[32];
	t_img			img[32];
	void			*mlx;
	void			*win;
	t_frame_data	frame;
	t_player		player;
	t_enemy			enemy;
	t_light			light;
	t_map			map;
	t_item			*item;
}					t_game;

#endif