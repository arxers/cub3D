/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:23:34 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/05 19:46:15 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <sys/time.h>

// UI
# define UI_PWL_TRUE "ENTER P-5000 POWERED WORK LOADER"
# define UI_PWL_FALSE "NOT ENOUGH FUEL CELLS!"
# define UI_DOOR "OPEN/CLOSE"

// Gameplay
# define TARGET_FPS 30
# define REQUIRED_ITEMS 3

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

// Map
# define MAP_CELL_SIZE 16
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

typedef struct s_fvec
{
	float			x;
	float			y;
}					t_fvec;

typedef struct s_vec
{
	int				x;
	int				y;
}					t_vec;

typedef struct s_img
{
	void			*img;
	char			*addr;
	t_vec			size;
	float			intensity;
	int				bits_per_pixel;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_coin
{
	t_fvec			pos;
	t_fvec			dist;
	int				collected;
}					t_coin;

typedef struct s_player
{
	t_fvec			pos;
	t_fvec			plane;
	t_fvec			dir;
	float			z;
	float			zoom;
	int				pitch;
}					t_player;

typedef struct s_enemy
{
	t_fvec			pos;
	t_fvec			dist;
	t_fvec			memory;
	t_fvec			last_dist;
	t_fvec			last_seen;
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
	int				**arr;
	t_vec			size;
	t_vec			offset;
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
	t_fvec			map;
	t_fvec			dir;
	t_fvec			side_dist;
	t_fvec			delta_dist;
	t_vec			pix;
	t_vec			step;
	float			wall_dist;
	int				draw_start;
	int				draw_end;
	char			side;
}					t_ray;

typedef struct s_texture_map
{
	t_img			*wall_tex;
	t_fvec			hit;
	t_vec			coords;
	float			tex_step;
}					t_tex;

typedef struct s_pwl
{
	t_img			item_img;
	t_img			overlay_img;
	t_coin			item;
	int				frame;
}					t_pwl;

typedef struct s_item
{
	t_img			img;
	t_coin			*arr;
	int				count;
	int				collected;
}					t_item;

typedef struct s_scene
{
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	char			*floor;
	char			*ceiling;
	unsigned int	hex_floor;
	unsigned int	hex_ceiling;
	char			*tmp_map_buf;
	char			**map;
	char			**map_bak;
	t_vec			map_dim;
	t_vec			p_pos;
	t_vec			pos_xeno;
	t_vec			pos_powerloader;
}					t_scene;

typedef struct s_game
{
	t_scene			scene;
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

// cleanup.c
void				ft_destroy_image(void *mlx_ptr, t_img *img);
void				free_int_array(int **output, int size);
int					cleanup(t_game *game, unsigned char status, char *msg);
void				error_handler(t_game *game, int status);

// image_utils.c
unsigned int		darken(unsigned int color, float factor);
float				set_intensity(t_light light, float dist);
void				draw_diagonal_lines(t_img *img, t_vec size,
						unsigned int color);
void				fill_img(t_img *img, unsigned int color);

// image_pixel_utils.c
void				set_pixel(t_img *img, int x, int y, unsigned int color);
void				set_pixel_alpha(t_img *img, int x, int y,
						unsigned int color);
unsigned int		get_pixel(t_img *img, int x, int y);

// image_primitives.c
void				brasenham(int *err, t_vec *start, t_vec d, t_vec s);
void				draw_rectangle(t_img *dst, t_vec origin, t_vec size,
						unsigned int color);
void				draw_circle(t_img *dst, t_vec origin, int radius,
						unsigned int color);
void				draw_circle_outline(t_img *dst, t_vec origin, int radius,
						unsigned int color);
void				draw_line(t_img *img, t_vec start, t_vec end,
						unsigned int color);

// image_copy_paste.c
void				put_img_scale_darken(t_vec ofs, t_img *src, t_img *dst,
						t_fvec scale);
void				put_img_scale_mid_bot(t_vec ofs, t_img *src, t_img *dst,
						t_fvec scale);
void				put_img_scale_mid(t_vec ofs, t_img *src, t_img *dst,
						t_fvec scale);
void				put_img_scale(t_vec offset, t_img *src, t_img *dst,
						t_fvec scale);
void				put_img(t_vec offset, t_img *src, t_img *dst);

// draw_primitives.c
void				draw_rectangle(t_img *dst, t_vec origin, t_vec size,
						unsigned int color);
void				draw_circle(t_img *dst, t_vec origin, int radius,
						unsigned int color);
void				draw_circle_outline(t_img *dst, t_vec origin, int radius,
						unsigned int color);
void				draw_line(t_img *img, t_vec start, t_vec end,
						unsigned int color);

// minimap.c
void				draw_tile(t_img *map, t_vec origin, int tile);
void				update_map_tiles(t_game *game);
void				draw_map_enemy(t_game *game);
void				draw_map_player(t_img *img, t_player p);
void				draw_minimap(t_game *game);

// init_game.c
void				init_player(t_game *game);
void				init_enemy(t_game *game);
void				init_items(t_game *game);
void				init_pwl(t_game *game);
int					init_game(t_game *game, t_scene scene);

// init_game_utils.c
void				init_player_dir(t_game *game);
int					count_tile(t_game *game, int n);

// init_image.c
int					init_img(void *mlx_ptr, t_img *img, int width, int height);
int					load_xpm(void *mlx, char *path, t_img *img);
int					load_pwl_xpms(t_game *game);
int					load_xpms(t_game *game);

// init_map.c
void				convert_row_to_ints(int *output_row, char *input_row);
int					**char_to_int_map(char **input);
int					init_minimap(t_game *game, t_vec map_grid_size);

// pwl_render.c
void				set_pwl_view(t_game *game, t_ray r);
void				render_pwl_sprite(t_game *game, t_ray r);
void				pwl_hit_check(t_game *game);
void				render_pwl_overlay(t_game *game);
void				render_pwl(t_game *game);

// item.c
void				render_item_sprite(t_game *game, t_coin item);
void				render_item(t_game *game);
int					same_position(t_fvec p1, t_fvec p2);
void				pickup_item(t_game *game);

// key_hooks.c
void				handle_keystate(unsigned int key, int state, t_game *game);
int					key_press(unsigned int key, t_game *game);
int					key_release(unsigned int key, t_game *game);

// key_specials.c
void				pause_game(t_game *game);
void				toggle_mouse(t_game *game);
int					exit_game(t_game *game);

// mouse_event.c
int					mwheel(unsigned int key, t_game *game);
int					mouse_event(unsigned int key, int x, int y, t_game *game);

// enemy_hunt.c
void				move_enemy_cardinal(t_game *game, int direction,
						t_fvec *new_pos);
void				move_enemy_diagonal(t_game *game, int direction,
						t_fvec *new_pos);
void				move_enemy(t_game *game, t_fvec *new_pos);
void				enemy_hunt(t_game *game);

// enemy_chase.c
void				set_player_look_at(t_player *player, t_fvec enemy_pos);
void				enemy_game_over(t_game *game);
void				enemy_open_door(t_game *game);
void				enemy_chase(t_game *game, float dist_sq, float speed);
void				update_enemy_pos(t_game *game);

// enemy_render.c
void				update_enemy_sprite(t_game *game);
void				render_enemy(t_game *game);
void				render_enemy_sprite(t_game *game);

// player_movement.c
void				calculate_movement(t_game *game, float *move_x,
						float *move_y);
void				normalize_movement(float *move_x, float *move_y);
void				handle_movement_xy(t_game *game, float speed);
void				handle_movement(t_game *game);

// player_look.c
void				vertical_look(t_game *game, float delta);
void				handle_mouselook(t_game *game);
void				handle_yaw(t_game *game, float speed, float old_dir_x,
						float old_plane_x);
void				handle_pitch(t_game *game);

// player_utils.c
int					out_of_bounds(t_fvec map, t_game *game);
void				unstuck_player(t_game *game, t_ray r);
int					check_collision(t_fvec *pos, t_fvec new_pos, float radius,
						t_game *game);

// raycasting.c
void				draw_wall_slices(t_game *game, t_ray *r, t_tex *tex);
void				calculate_wall_projection(t_game *game, t_ray *r,
						t_tex *tex);
void				assign_wall_textures(t_game *game, t_ray *r, t_tex *tex);
void				assign_tile_textures(t_game *game, t_ray *r, t_tex *tex);
void				render_walls(t_game *game);

// dda.c
void				set_ray_direction(t_game *game, t_ray *r, float camera_x,
						int incl_zoom);
void				set_ray_step_direction(t_game *game, t_ray *r);
void				set_dda_step_side(t_ray *r);
int					dda(t_ray *r, t_game *game);

// dda_special.c
void				init_ray_to_target(t_game *game, t_ray *r,
						t_fvec target_pos);
int					dda_to_target(t_game *game, t_ray *r, t_fvec target_pos);
int					dda_interact(t_ray *r, t_game *game);

// display_ui.c
void				display_fps_counter(t_game *game);
void				display_msg(t_game *game);
void				display_pause_screen(t_game *game);

// interact.c
void				display_ui_msg(t_game *game, char *key, char *msg);
void				interact_door(t_game *game, t_ray r);
void				interact_pwl(t_game *game);
void				check_interact(t_game *game, int *tile_hit, t_ray *r);
void				interact(t_game *game);

// background.c
int					init_bg(t_game *game, int ceiling, int floor);
void				draw_bg(t_game *game);

// utils.c
int					delay_ms(unsigned int ms, struct timeval *timer);
int					should_render_frame(t_game *game);
float				dot_product(t_fvec a, t_fvec b);

#endif
