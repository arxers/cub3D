typedef struct s_scene
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	*floor;
	char	*ceiling;
	char	*tmp_map_buf;
	char	**map; // (char **)
	//int		*f_rgb;
	//int		*c_rgb;
} t_scene;

int		check_n_cmdline_args(int ac);
int		is_map_a_dot_cub_file(char *s);
int		is_map_file_openable(char *mapfile);
int		load_scene(char *mapfile, t_scene *scene);
int		load_scene_details(int map_fd, t_scene **scene);

int		is_empty_line(char *s); // return 1, when arg is indeed an empty line
int		is_start_with_expected_identifier(char *s);

void	free_char_map(char **arr);
void	free_scene_struct(t_scene *s);
int		is_first_detail(char *s, t_scene *scene);
//int		assign_detail_to_scene_struct(char *s, t_scene **scene);
int		assign_f_or_c_to_scene_struct(char *s, t_scene **scene);
int		assign_wall_to_scene_struct(char *s, t_scene **scene);
int		is_all_six_scene_details_present(t_scene *scene);
char	*prepare_a_wall(char *s);
int		prepare_walls(t_scene **scene);

int		is_end_with_xpm(char *s);
int		ft_arr_len(char **arr);
int		is_valid_rgb_value(char *s);
int		is_valid_rgb_array(char *s);
int		is_six_details_valid(t_scene *scene);

int		is_map_char_valid(char *s);
int		trim_tmp_map_buf(t_scene **scene);
int		is_tmp_map_buf_split_by_empty_line(char *s);


// pending ?
int 	is_wall_texture(char *s);

// for debugging only
void	print_scene_struct(t_scene *scene);
void	print_arr(char **arr);
