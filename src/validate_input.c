#include "../inc/cub3D.h"

// when success, return 0
// when failure return 1

// check num of cmdline args
void check_n_cmdline_args(int ac)
{
	if (ac != 2)
	{
		ft_putstr_fd("cub3D: Invalid number of arguments\n", 2);
		ft_putstr_fd("cub3D: usage: cub3D [*.cub]\n", 2);
		exit(1);
	}
}

// check if map ends with ".cub"
void	is_map_a_dot_cub_file(char *s)
{
	int	len;
	
	len = ft_strlen(s);
	if ((s[len - 1] == 'b') && \
		(s[len - 2] == 'u') && \
		(s[len - 3] == 'c') && \
		(s[len - 4] == '.') \
		)
		return ;
	else
	{
		ft_putstr_fd("cub3D: Map does not end in .cub\n", 2);
		ft_putstr_fd("cub3D: usage: cub3D [*.cub]\n", 2);
		exit(1);
	}
}

void	is_map_file_openable(char *mapfile)
{
	int map_fd;
	
	map_fd = open(mapfile, O_RDONLY);
	if (map_fd == -1)
	{
		ft_putstr_fd("cub3D: Map cannot be opened\n", 2);
		exit(1);
	}
	return ;
}

t_scene	*alloc_scene(void)
{
	t_scene *tmp_ptr;
	
	tmp_ptr = ft_calloc(1, sizeof(t_scene));
	if (!tmp_ptr)
	{
		ft_putstr_fd("cub3D: Cannot alloc memory for scene\n", 2);
		exit(1);
	}
	else
		return (tmp_ptr);
}

//# DONE above
//##############################################################################
//# pending below

int is_end_with_xpm(char *s)
{
	int	len;
	
	len = ft_strlen(s);
	if ((s[len - 1] == 'm') && \
		(s[len - 2] == 'p') && \
		(s[len - 3] == 'x') && \
		(s[len - 4] == '.') \
		)
		return (0);
	else
		return (1);
}

/*
as long as line starts with any one of the six possible identifiers, return 0
else return 1 (error)
*/
int	is_start_with_expected_identifier(char *s)
{
	if (!ft_strncmp(s, "NO ", 3) 
		|| !ft_strncmp(s, "SO ", 3)
		|| !ft_strncmp(s, "EA ", 3)
		|| !ft_strncmp(s, "WE ", 3)
		|| !ft_strncmp(s, "F ", 2)
		|| !ft_strncmp(s, "C ", 2)
		)
		return (0);
	else
		return (1);
}

/*
if line does NOT end with 4 chars ".xpm", return 1 (error)
if line does NOT start with expected identifier, return 1 (error) 

NOTE. expected identifiers:
first 3 chars: "NO ", "SO ", "EA ", "WE "
first 2 chars: "F ", "C "

if reach here, then return 0 (success)
*/
int is_wall_texture(char *s)
{
	printf("is_wall_texture()\n");
	if ((is_start_with_expected_identifier(s) == 1))
		return (1);
	else
		return (0);
}


/*
if any of the scene details (less map) is NULL, return 1 (ERROR!)
else return 0 (SUCCESS)
*/

/*
static int	is_scene_details_exceptmap_loaded(t_scene *scene)
{
	if (!(scene->no) || !(scene->so) || !(scene->ea) || !(scene->we) 
		|| !(scene->floor) || !(scene->ceiling))
		return (1);
	else
		return (0);
}
*/

/*
read .cub file, line by line, using get_next_line()
check if current line begins with any of the 5 expected identifiers:
"NO "
"SO "
"EA "
"WE "
"F "
"C "

if something else, read, and free, ie. skip the map!

after reading,
check if 6 lines are present in t_scene struct

NOTE. line returned from GNL, contains a terminating '\n'

*/
void	load_scene_details(int map_fd, t_scene **scene)
{
	char 	*line;
	int		n;
	int		n_total_lines;
	int		n_texture_lines;
	(void)	scene;
	
	n = 0;
	n_total_lines = 0;
	n_texture_lines = 0;
	line = get_next_line(map_fd);
	while (line)
	{
		n_total_lines++;
		if (is_start_with_expected_identifier(line) == 0)
		{
			n_texture_lines += 1;
			printf("%s", line);					
		}
		//printf("line contents: %s", line);
		//is_wall_texture(line);
		/* 
		// if all scene details except map, are loaded, then stop loading
		if (is_scene_details_except_map_loaded(*scene)) 
			break ;
		
		if (is_wall_texture(line)) // update scene struct with ONE wall texture line
		{
			// error handling
			// finish reading and then flush gnl buffer, free_members_and_scene(), exit(1)
			
		}
		*/
		
		
		
		
		
		/*
		else if (is_floor_or_ceiling(line)) // update floor/ceiling with ONE line of color values
		{
			// pending
		}
		else // neither wall nor floor/ceiling
		{
			free(line);
			line = get_next_line(map_fd);
		}
		*/
		free(line);
		line = get_next_line(map_fd);
	}
	printf("\n");
	printf("n_texture_lines: %d\n", n_texture_lines);	// expect 6 for map.cub
	printf("n_total_lines: %d\n", n_total_lines);		// expect 29 for map.cub
	// if all scene details except map, are NOT loaded, then free the scene members + scene, and exit
/*
	if (!is_scene_details_exceptmap_loaded(*scene))
	{
		free_scene_and_its_members(scene);
		ft_putstr_fd("cub3D: Cannot load wall(s)/floor/ceiling\n", 2);
		exit(1);
	}
*/
}


void	load_scene_except_map(char *mapfile, t_scene *scene)
{
	int map_fd;
	
	map_fd = open(mapfile, O_RDONLY);
	if (map_fd == -1)
	{
		free(scene);
		ft_putstr_fd("cub3D: Map cannot be opened\n", 2);
		exit(1);
	}
	load_scene_details(map_fd, &scene);

/*
	if(!is_scene_details_exceptmap_loaded(scene))
	{
		free_scene_and_its_members();
		ft_putstr_fd("cub3D: Cannot load wall(s)/floor/ceiling\n", 2);
		exit(1);	
	}
*/
}
	


/*
void load_map()
{
	// check if is_wall_texture() / is_floor_or_ceiling() / neither, and iterate past these lines
	// read map line by line, until EOF
	// join map lines, into one single line (as a (char *)), NOTE. \n will be included!
}
*/

/*
checks if "\n\n" sequence is present in (char *) map as single line
if present, means empty line in map, then reject map, 
set, char **map = NULL, in 'scene' struct

void is_empty_line_in_singleline_map()
*/

/*
if any of the 7 scene details are NULL
free(scene)

exit(1)
*/

/*
void is_all_seven_scene_details_present(t_scene *scene)
{
	if (!(scene->no) || !(scene->so) || !(scene->ea) || !(scene->we) 
		|| !(scene->floor) || !(scene->ceiling) || !(scene->map))
	{
		// free members in 'scene' struct
		free(scene); // free the 'scene' struct's memory
		ft_putstr_fd("cub3D: Missing some scene details\n", 2);
		exit(1);	
	}
}
*/
// if all seven scene details are present,
// ft_split the map in a single line, into a (char **), using '\n' as delimiter
// free the (char *) singleline map
