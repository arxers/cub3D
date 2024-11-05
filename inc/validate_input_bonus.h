/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:10:57 by jsu               #+#    #+#             */
/*   Updated: 2024/11/05 21:03:16 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_INPUT_BONUS_H
# define VALIDATE_INPUT_BONUS_H
# include "cub3D_bonus.h"

// validate_cub_file_bonus.c
int		check_n_cmdline_args(int ac);
int		is_map_a_dot_cub_file(char *s);
int		is_map_file_openable(char *mapfile);
int		is_map_a_directory(char *mapfile);
void	free_scene_struct(t_scene *s);

// load_scene_details_bonus.c
int		load_scene(char *mapfile, t_scene *scene);
int		load_scene_details(int map_fd, t_scene **scene);
int		is_all_six_scene_details_present(t_scene *scene);
int		load_map_buffer(char *line, int map_fd, t_scene **scene);
void	flush_gnl(char **line, int map_fd);

// load_scene_details_to_struct_bonus.c
int		load_scene_details_to_struct(char **line, int map_fd, t_scene **scene);
int		is_start_with_expected_identifier(char *s);
int		is_first_detail(char *s, t_scene *scene);
int		assign_wall_to_scene_struct(char *s, t_scene **scene);
int		assign_f_or_c_to_scene_struct(char *s, t_scene **scene);

// prepare_walls_bonus.c
int		prepare_walls(t_scene **scene);
char	*prepare_a_wall(char *s);
void	free_char_map(char **arr);
int		is_six_details_valid(t_scene *scene);
int		is_end_with_xpm(char *s);

// is_valid_rgb_array_bonus.c
int		is_valid_rgb_array(char *s);
int		ft_count_char(char *s, char c);
int		is_valid_rgb_value(char *s);
int		convert_rgb_array_to_int(char *s);

// is_map_char_valid_bonus.c
int		is_map_char_valid(char *s);
int		process_map(t_scene *scene);
int		trim_tmp_map_buf(t_scene **scene);
void	replace_space_with_zero(char *s);
int		is_tmp_map_buf_split_by_empty_line(char *s);

// process_map_bonus.c
int		init_map_array(char ***map, char **map_temp, t_scene *scene);
void	count_map_area(char **map_temp, t_scene *scene);
void	load_map_data(char **s, t_scene *scene);
void	load_map_bak_data(char **s, t_scene *scene);

// is_map_valid_bonus.c
int		is_map_valid(t_scene *scene);
int		is_num_player_valid(char **map);
int		count_char_in_map(char **map, char ch);
int		load_player_pos(char **map, t_scene *scene);
void	ff_bonus(int i, int j, t_scene *s);

// load_chars_bonus.c
int		is_num_xeno_valid(char **map);
int		load_xeno_pos(char **map, t_scene *scene);
int		is_num_powerloader_valid(char **map);
int		load_powerloader_pos(char **map, t_scene *scene);
int		is_num_collectibles_valid(char **map);

// is_fill_char_at_map_border_bonus.c
int		is_fill_char_at_map_border(t_scene *scene);
int		is_fill_char_at_toprow(t_scene *s);
int		is_fill_char_at_botrow(t_scene *s);
int		is_fill_char_at_lcol(t_scene *s);
int		is_fill_char_at_rcol(t_scene *s);

#endif
