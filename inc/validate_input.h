#ifndef VALIDATE_INPUT_H
# define VALIDATE_INPUT_H
# include "cub3D.h"

// for debugging only
void				print_2d_map(char **s);
void				print_scene_struct(t_scene *scene);
void				print_arr(char **arr);

// "clean up" related functions
void				flush_gnl(char **line, int map_fd);
void				free_char_map(char **arr);
void				free_scene_struct(t_scene *s);

int					check_n_cmdline_args(int ac);
int					is_map_a_dot_cub_file(char *s);
int					is_map_file_openable(char *mapfile);

// LOAD first six details
int					is_start_with_expected_identifier(char *s);
int					is_first_detail(char *s, t_scene *scene);
int					assign_f_or_c_to_scene_struct(char *s, t_scene **scene);
int					assign_wall_to_scene_struct(char *s, t_scene **scene);
int					is_all_six_scene_details_present(t_scene *scene);

char				*prepare_a_wall(char *s);
int					prepare_walls(t_scene **scene);

// CHECK first six details
int					is_end_with_xpm(char *s);
int					ft_arr_len(char **arr);
int					is_valid_rgb_value(char *s);
int					is_valid_rgb_array(char *s);
int					is_six_details_valid(t_scene *scene);

// LOAD map
int					load_map_buffer(char *line, int map_fd, t_scene **scene);
int					load_scene_details(int map_fd, t_scene **scene);

int					is_map_char_valid_bonus(char *s);
int					is_map_char_valid_mandatory(char *s);
int					trim_tmp_map_buf(t_scene **scene);
void				replace_space_with_zero(char *s);
int					is_tmp_map_buf_split_by_empty_line(char *s);

void				count_map_area(char **map_temp, t_scene *scene);
int					init_map_array(char ***map, char **map_temp,
						t_scene *scene);
// int					init_map_bak_array(char **map_temp, t_scene *scene);
void				load_map_data(char **s, t_scene *scene);
void				load_map_bak_data(char **s, t_scene *scene);

// CHECK map
int					count_char_in_map(char **map, char ch);
int					is_num_player_valid(char **map);
int					load_player_pos(char **map, t_scene *scene);

// CHECK map (need the extra four functions below, for BONUS)
int					is_num_xeno_valid(char **map);
int					load_xeno_pos(char **map, t_scene *scene);
int					is_num_powerloader_valid(char **map);
int					load_powerloader_pos(char **map, t_scene *scene);

int					is_fill_char_at_toprow(t_scene *s);
int					is_fill_char_at_botrow(t_scene *s);
int					is_fill_char_at_lcol(t_scene *s);
int					is_fill_char_at_rcol(t_scene *s);
int					is_fill_char_at_map_border(t_scene *scene);
void				ff_mandatory(int i, int j, t_scene *s);

void				ff_bonus(int i, int j, t_scene *s);

// wrapper aka start here
int					load_scene(char *mapfile, t_scene *scene);

#endif
