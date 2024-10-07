typedef struct s_scene
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	**floor;	// (char **)
	char	**ceiling;	// (char **)
	char	**map;		// (char **)
} t_scene;

void	check_n_cmdline_args(int ac);
void	is_map_a_dot_cub_file(char *s);
void	is_map_file_openable(char *mapfile);
t_scene	*alloc_scene(void);
