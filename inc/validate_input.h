typedef struct s_scene
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	*floor;
	int		f_rgb[3];
	char	*ceiling;
	int		c_rgb[3];
	char	**map; // (char **)
} t_scene;

int		check_n_cmdline_args(int ac);
int		is_map_a_dot_cub_file(char *s);
int		is_map_file_openable(char *mapfile);
int		load_scene_except_map(char *mapfile, t_scene *scene);
int		load_scene_details(int map_fd, t_scene **scene);

int		is_empty_line(char *s); // return 1, when arg is indeed an empty line
int		is_start_with_expected_identifier(char *s);

void	free_char_map(char **arr);
void	free_scene_struct(t_scene *s);
void	assign_detail_to_scene_struct(char *s, t_scene **scene);

int		is_all_six_scene_details_present(t_scene *scene);

int 	is_wall_texture(char *s);
int		is_end_with_xpm(char *s);

// for debugging only
void	print_scene_struct(t_scene *scene);
