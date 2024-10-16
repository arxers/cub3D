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

/*
as long as there is a single char that is NOT "whitespace"
	return 0 (line is NOT an empty line)
else only when all chars are "whitespace"
	then return 0 (success, line is indeed an empty line)
*/
int is_empty_line(char *s)
{
	int i;
	
	i = 0;
	while(s[i])
	{
		if (s[i] != '\t' 
			&& s[i] != '\n'
			&& s[i] != '\v'
			&& s[i] != '\f'
			&& s[i] != '\r'
			&& s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

/*
as long as line starts with any one of the six possible identifiers, return 1
else return 0 (line does NOT start with an expected identifier)
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
		return (1);
	else
		return (0);
}

void	assign_detail_to_scene_struct(char *s, t_scene **scene)
{
	if (ft_strncmp(s, "NO ", 3) == 0 && (*scene)->no == NULL)
		(*scene)->no = ft_strdup(ft_strtrim(s, "\n"));
	else if (ft_strncmp(s, "SO ", 3) == 0 && (*scene)->so == NULL)
		(*scene)->so = ft_strdup(ft_strtrim(s, "\n"));
	else if (ft_strncmp(s, "EA ", 3) == 0 && (*scene)->ea == NULL)
		(*scene)->ea = ft_strdup(ft_strtrim(s, "\n"));
	else if (ft_strncmp(s, "WE ", 3) == 0 && (*scene)->we == NULL)
		(*scene)->we = ft_strdup(ft_strtrim(s, "\n"));
	else if (ft_strncmp(s, "F ", 2) == 0 && (*scene)->floor == NULL)
		(*scene)->floor = ft_strdup(ft_strtrim(s, "\n"));
	else if (ft_strncmp(s, "C ", 2) == 0 && (*scene)->ceiling == NULL)
		(*scene)->ceiling = ft_strdup(ft_strtrim(s, "\n"));
}

//# DONE above
//##############################################################################
//# pending below



/*
only if ALL of the six details are present, then return 1
else return 0 (one or more of the details are missing)
*/
int	is_all_six_scene_details_present(t_scene *scene)
{
	if ((scene->no != NULL) 
		&& (scene->so != NULL) 
		&& (scene->ea != NULL) 
		&& (scene->we != NULL) 
		&& (scene->floor != NULL) 
		&& (scene->ceiling != NULL))
		return (1);
	else
		return (0);
}

void	print_scene_struct(t_scene *scene)
{
	printf("\nCurrent state of t_scene struct:\n");
	printf("NO texture: %s\n", scene->no);
	printf("SO texture: %s\n", scene->so);
	printf("EA texture: %s\n", scene->ea);
	printf("WE texture: %s\n", scene->we);
	printf("F color: %s\n", scene->floor);
	printf("C color: %s\n", scene->ceiling);
//	printf("map ptr: %p", scene->map);
}

/*
ft_split() the line, with ' ' as delimiter
check if ft_split() returns TWO valid (char *) arrays
if arr[0]  == "NO ", and scene->no == NULL
{
	scene->no = ft_strtrim(arr[1], "\n"); // trim the trailing newline, and assign to member in scene struct
}

int	proc_scene_detail(char *s, t_scene *scene)
{

}
*/

// ft_strcmp(&(s1[len - 4]), ".xpm")

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
if line does NOT end with 4 chars ".xpm", return 1 (error)
if line does NOT start with expected identifier, return 1 (error) 

NOTE. expected identifiers:
first 3 chars: "NO ", "SO ", "EA ", "WE "
first 2 chars: "F ", "C "

if reach here, then return 0 (success)

int is_wall_texture(char *s)
{
	printf("is_wall_texture()\n");
	if ((is_start_with_expected_identifier(s) == 1))
		return (1);
	else
		return (0);
}
*/

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

if current line STARTS with any of the 6 expected identifiers:
"NO "
"SO "
"EA "
"WE "
"F "
"C "
then process the line:

ft_split() the line, with ' ' as delimiter
check if ft_split() returns TWO valid (char *) arrays
if arr[0]  == "NO ", and scene->no == NULL
{
	scene->no = ft_strtrim(arr[1], "\n"); // trim the trailing newline, and assign to member in scene struct
}

if something else, read, and free, ie. skip the map!

after reading,
check if 6 lines are present in t_scene struct

NOTE. line returned from GNL, contains a terminating '\n'

*/
void	load_scene_details(int map_fd, t_scene **scene)
{
	char 	*line;
	(void)	scene;
	
	line = get_next_line(map_fd); // gnl() will return a line, ending with '\n'
	while (line)
	{
		//printf("%s: %zu\n\n", line, ft_strlen(line));
		//printf("%s: %zu\n\n", ft_strtrim(line, "\n"), ft_strlen(ft_strtrim(line, "\n")));
		if (is_all_six_scene_details_present(*scene) == 1)
		{
			printf("found all six scene details!\n");		
			return ; // because we have accepted ENOUGH scene details
		}

		if (is_empty_line(line) == 1)
		{
			free(line);
			line = get_next_line(map_fd);
			printf("found an empty line\n");
			continue ;
		}
		
		if (is_start_with_expected_identifier(line) == 1)
		{
			printf("found one scene detail!\n"); // remove, for debugging only
			assign_detail_to_scene_struct(line, scene);
		}
		
		// if is_scene_struct_valid()
		

		
		
		
		
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
	print_scene_struct(scene);
	
	
	// first map line, is line after texture line, that is not just newline
	// last map line, is the line before the first newline

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




// if all seven scene details are present,
// ft_split the map in a single line, into a (char **), using '\n' as delimiter
// free the (char *) singleline map
