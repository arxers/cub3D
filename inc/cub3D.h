/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:23:34 by jaslim            #+#    #+#             */
/*   Updated: 2024/10/07 14:43:01 by jaslim           ###   ########.fr       */
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

// UI
# define UI_PWL_TRUE "ENTER P-5000 POWERED WORK LOADER"
# define UI_PWL_FALSE "NOT ENOUGH FUEL CELLS!"
# define UI_DOOR "OPEN/CLOSE"

// Gameplay
# define REQUIRED_ITEMS 2

// Movement Constants
# define MOUSE_SEN 0.0025
# define ROT_SPD 0.0025
# define RUN_SPD 2
# define PLAYER_SPD 0.002
# define ENEMY_SPD 0.0025
# define PLAYER_RADIUS 0.20
# define ENEMY_RADIUS 0

// Raycasting
# define VERTICAL 0
# define HORIZONTAL 1

// Resolution
# define RES_X 1024
# define RES_Y 768
# define RES_X2 512
# define RES_Y2 384
# define WALL 64

// map
# define MAP_CELL_SIZE 24
# define MAP_COLOR 0x0ADAF3

// Colors
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define MAGENTA 0xFF00FF

// Bounds
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
	T_PWL0,
	T_PWL1,
	T_PWL2,
	T_PWL3,
	T_PWL4,
	T_PWL5,
	T_PWL6,
	T_PWL7,
	T_PWL_ARM0,
	T_PWL_ARM1,
	T_PWL_ARM2,
	T_PWL_ARM3,
	T_PWL_ARM4,
	T_PWL_ARM5,
	T_PWL_ARM6,
	T_ITEM,
	IMG_MAX
}					t_texture;

typedef enum e_state
{
	S_UP,
	S_DOWN,
	S_LEFT,
	S_RIGHT,
	S_ROT_U,
	S_ROT_D,
	S_ROT_L,
	S_ROT_R,
	S_INTERACT,
	S_MAP_DISABLE,
	S_MAP_BIG,
	S_MOUSE,
	S_RUN,
	S_SPACE,
	S_PAUSE,
	S_ENEMY_ICON,
	S_ENEMY_PATH,
	S_ENEMY_VISION,
	S_ENEMY_DEAD,
	S_CAUGHT,
	S_PUNCHING,
	STATE_MAX,
}					t_state;

typedef enum e_tiles
{
	TILE_ITEM = -3,
	TILE_DOOR_OPEN,
	TILE_FLOOR = 0,
	TILE_WALL,
	TILE_DOOR,
	TILE_PWL
}					t_tiles;

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
	TIMER_PWL,
	TIMER_ENEMY,
	TIMER_ENEMY_MAP,
	TIMER_ENEMY_PATH,
	TIMER_MAX,
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
	float			intensity;
	int				bits_per_pixel;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_coin
{
	t_fpoint		pos;
	t_fpoint		dist;
	t_img			*img;
	int				collected;
}					t_coin;

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
	char			update;
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
	int				draw_start;
	int				draw_end;
	char			side;
}					t_ray;

typedef struct s_texture_map
{
	t_img			*wall_tex;
	t_point			coords;
	t_fpoint		hit;
	float			tex_step;
}					t_texture_map;

typedef struct s_pwl
{
	t_coin			item;
	t_img			img;
	int				frame;
}					t_pwl;

typedef struct s_item
{
	t_coin			*array;
	int				count;
	int				collected;
}					t_item;

typedef struct s_game
{
	t_img			img[IMG_MAX];
	char			state[STATE_MAX];
	struct timeval	timer[TIMER_MAX];
	void			*mlx;
	void			*win;
	t_frame_data	frame;
	t_player		player;
	t_enemy			enemy;
	t_light			light;
	t_map			map;
	t_pwl			pwl;
	t_item			item;
}					t_game;

#endif