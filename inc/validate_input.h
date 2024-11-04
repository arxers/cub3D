/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:10:57 by jsu               #+#    #+#             */
/*   Updated: 2024/11/04 15:10:59 by jsu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_INPUT_H
# define VALIDATE_INPUT_H
# include "cub3D.h"

// for debugging only
void	print_2d_map(char **s);
void	print_scene_struct(t_scene *scene);
void	print_arr(char **arr);

// validate_bonus_cub_file.c // swap 1 function: load_x_scene()
int		check_n_cmdline_args(int ac);
int		is_map_a_dot_cub_file(char *s);
int		is_map_file_openable(char *mapfile);
int		load_bonus_scene(char *mapfile, t_scene *scene);
//int	load_mandatory_scene(char *mapfile, t_scene *scene);
void	free_scene_struct(t_scene *s);

// load_scene_details.c
int		load_scene_details(int map_fd, t_scene **scene);
int		is_all_six_scene_details_present(t_scene *scene);
int		load_map_buffer(char *line, int map_fd, t_scene **scene);
void	flush_gnl(char **line, int map_fd);

// load_scene_details_to_struct.c
int		load_scene_details_to_struct(char **line, int map_fd, t_scene **scene);
int		is_start_with_expected_identifier(char *s);
int		is_first_detail(char *s, t_scene *scene);
int		assign_wall_to_scene_struct(char *s, t_scene **scene);
int		assign_f_or_c_to_scene_struct(char *s, t_scene **scene);

// prepare_walls.c
int		prepare_walls(t_scene **scene);
char	*prepare_a_wall(char *s);
void	free_char_map(char **arr);
int		is_six_details_valid(t_scene *scene);
int		is_end_with_xpm(char *s);

// is_valid_rgb_array.c
int		is_valid_rgb_array(char *s);
int		ft_count_char(char *s, char c);
int		is_valid_rgb_value(char *s);
int		convert_rgb_array_to_int(char *s);

// is_bonus_map_char_valid.c // swap 1 function: is_x_map_char_valid()
int		is_bonus_map_char_valid(char *s);
//int	is_mandatory_map_char_valid(char *s);
int		process_map(t_scene *scene);
int		trim_tmp_map_buf(t_scene **scene);
void	replace_space_with_zero(char *s);
int		is_tmp_map_buf_split_by_empty_line(char *s);

// process_map.c
int		init_map_array(char ***map, char **map_temp, t_scene *scene);
void	count_map_area(char **map_temp, t_scene *scene);
void	load_map_data(char **s, t_scene *scene);
void	load_map_bak_data(char **s, t_scene *scene);

// is_bonus_map_valid.c // swap 2 functions: is_x_map_valid(), ff_x())
int		is_bonus_map_valid(t_scene *scene);
//int	is_mandatory_map_valid(t_scene *scene);
int		is_num_player_valid(char **map);
int		count_char_in_map(char **map, char ch);
int		load_player_pos(char **map, t_scene *scene);
void	ff_bonus(int i, int j, t_scene *s);
//void	ff_mandatory(int i, int j, t_scene *s);

// load_bonus_chars.c (REMOVE FOR MANDATORY)
int		is_num_xeno_valid(char **map);
int		load_xeno_pos(char **map, t_scene *scene);
int		is_num_powerloader_valid(char **map);
int		load_powerloader_pos(char **map, t_scene *scene);
int		is_num_collectibles_valid(char **map);

// is_fill_char_at_map_border.c
int		is_fill_char_at_map_border(t_scene *scene);
int		is_fill_char_at_toprow(t_scene *s);
int		is_fill_char_at_botrow(t_scene *s);
int		is_fill_char_at_lcol(t_scene *s);
int		is_fill_char_at_rcol(t_scene *s);
#endif
