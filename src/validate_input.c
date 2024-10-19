#include "../inc/cub3D.h"

void	print_scene_struct(t_scene *scene)
{
	printf("\nCurrent state of t_scene struct:\n");
	printf("NO texture: %s\n", scene->no);
	printf("SO texture: %s\n", scene->so);
	printf("EA texture: %s\n", scene->ea);
	printf("WE texture: %s\n", scene->we);
	printf("%s\n", scene->floor);
	printf("%s\n", scene->ceiling);
	printf("map ptr: %p\n", scene->map);
	printf("f_rgb: %p\n", scene->f_rgb);
	printf("c_rgb: %p\n", scene->c_rgb);
}

void	print_arr(char **arr)
{
	int i;
	
	i = 0;
	printf("print_arr() eg. result of ft_split()\n");
	while (arr[i] != NULL)
	{
		printf("%d: %s\n", i, arr[i]);
		i++;
	}
}

void flush_gnl(char *line, int map_fd)
{
	while (line)
	{
		free(line);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	line = NULL;
}

void free_char_map(char **arr)
{
	int i;
	
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void free_scene_struct(t_scene *s)
{
	if (s->no != NULL)
		free(s->no);
	if (s->so != NULL)
		free(s->so);
	if (s->ea != NULL)
		free(s->ea);
	if (s->we != NULL)
		free(s->we);
	if (s->floor != NULL)
		free(s->floor);
	if (s->ceiling != NULL)
		free(s->ceiling);
	if (s->map != NULL)
		free_char_map(s->map);
	if (s->f_rgb != NULL)
		free(s->f_rgb);
	if (s->c_rgb != NULL)
		free(s->c_rgb);
}



/* 
check num of cmdline args
if argc != 2, return -1 (error)
else return 0
*/
int check_n_cmdline_args(int ac)
{
	if (ac != 2)
	{
		ft_putstr_fd("cub3D: Invalid number of arguments\n", 2);
		ft_putstr_fd("cub3D: usage: cub3D [*.cub]\n", 2);
		return(-1);
	}
	return (0);
}

/* 
check if map ends with ".cub"
if <map file> ends in ".cub", return 0
else return -1
*/
int	is_map_a_dot_cub_file(char *s)
{
	int	len;
	
	len = ft_strlen(s);
	if ((s[len - 1] == 'b') && \
		(s[len - 2] == 'u') && \
		(s[len - 3] == 'c') && \
		(s[len - 4] == '.') \
		)
		return (0);
	else
	{
		ft_putstr_fd("cub3D: Map does not end in .cub\n", 2);
		ft_putstr_fd("cub3D: usage: cub3D [*.cub]\n", 2);
		return (-1);
	}
}

/*
if file can be opened, then return 0
else return -1
*/
int	is_map_file_openable(char *mapfile)
{
	int map_fd;
	
	map_fd = open(mapfile, O_RDONLY);
	if (map_fd == -1)
	{
		ft_putstr_fd("cub3D: Map cannot be opened\n", 2);
		return (-1);
	}
	return (0);
}

/*
if line starts with any one of the six possible identifiers, return 0 (success)
else return -1 (error, line does NOT start with an expected identifier)
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
		return (-1);
}

void	assign_detail_to_scene_struct(char *s, t_scene **scene)
{
	if (ft_strncmp(s, "NO ", 3) == 0 && (*scene)->no == NULL)
		(*scene)->no = ft_strdup(s);
	else if (ft_strncmp(s, "SO ", 3) == 0 && (*scene)->so == NULL)
		(*scene)->so = ft_strdup(s);
	else if (ft_strncmp(s, "EA ", 3) == 0 && (*scene)->ea == NULL)
		(*scene)->ea = ft_strdup(s);
	else if (ft_strncmp(s, "WE ", 3) == 0 && (*scene)->we == NULL)
		(*scene)->we = ft_strdup(s);
	else if (ft_strncmp(s, "F ", 2) == 0 && (*scene)->floor == NULL)
		(*scene)->floor = ft_strdup(s);
	else if (ft_strncmp(s, "C ", 2) == 0 && (*scene)->ceiling == NULL)
		(*scene)->ceiling = ft_strdup(s);
}

/*
only if ALL of the six details are present, then return 0 (success)
else return -1 (error; one or more of the details are missing)
*/
int	is_all_six_scene_details_present(t_scene *scene)
{
	if ((scene->no != NULL) 	
		&& (scene->so != NULL) 
		&& (scene->ea != NULL) 
		&& (scene->we != NULL) 
		&& (scene->floor != NULL) 
		&& (scene->ceiling != NULL))
		return (0);
	else
		return (-1);
}

/*
try to load 6 expected lines, into t_scene struct
if invalid line:
	print error msg to stderr
	flush gnl buffer AND close fd
*/
int	load_scene_details(int map_fd, t_scene **scene)
{
	char 	*line;
	
	line = get_next_line(map_fd);
	while (line)
	{
		if (is_all_six_scene_details_present(*scene) == 0)
		{
			flush_gnl(line, map_fd); // temporary! remove after implementing read_map()
			return (0); // call read_map() here
		}
		if (ft_strcmp(line, "\n") == 0)
		{
			free(line);
			line = get_next_line(map_fd);
			continue ;
		}
		else if (is_start_with_expected_identifier(line) == 0)
			assign_detail_to_scene_struct(line, scene);
		else
		{
			ft_putstr_fd("cub3D: Invalid/missing line for scene details\n", 2);
			flush_gnl(line, map_fd);
			return (-1);
		}		
		free(line);
		line = get_next_line(map_fd);
	}
	return (0);
}

/* 
ft_split, the passed in arg
ft_strdup, the second array from the ft_split result
ft_strtrim, the ft_strdup result
	
credits to @filim, for helping me "over the hump"!
*/
char	*prepare_a_wall(char *s)
{
	char **arr;
	char *tmp;
	char *res;
	
	tmp = NULL;
	arr = NULL;
	res = NULL;
	arr = ft_split(s, ' ');
	if (!arr)
		return (NULL);
	free(s);
	tmp = ft_strdup(arr[1]);
	if (!tmp)
		return (NULL);	
	free_char_map(arr);
	res = ft_strtrim(tmp, "\n");
	if (!res)
		return (NULL);
	free(tmp);
	return (res);
}

/* 
wrapper + retval check for prepare_a_wall()
*/
int	prepare_walls(t_scene **scene)
{
	(*scene)->no = prepare_a_wall((*scene)->no);
	(*scene)->so = prepare_a_wall((*scene)->so);
	(*scene)->ea = prepare_a_wall((*scene)->ea);
	(*scene)->we = prepare_a_wall((*scene)->we);	
	if ((*scene)->no == NULL || \
		(*scene)->so == NULL || \
		(*scene)->ea == NULL || \
		(*scene)->we == NULL)
		return (-1);
	return (0);
}

//# DONE above
//##############################################################################
//# pending below

/*
ft_split, the passed in arg, space as delimiter 		// F 0,42,255\n
ft_strdup, the second array from the ft_split result	// 0,42,255\n
ft_strtrim, the ft_strdup result						// 0,42,255

NOTE. have to ft_split() a SECOND TIME!, 				
ft_split, the ft_strtrim result, comma as delimiter

*/
int	*prepare_a_surface(char *s)
{
/*
	char **arr;
	char *tmp;
	char *res;
	
	tmp = NULL;
	arr = NULL;
	res = NULL;
*/	
	printf("%s\n", prepare_a_wall(s));
	
	return (NULL);
}



int	prepare_floor_ceiling(t_scene **scene)
{
	(*scene)->f_rgb = prepare_a_surface((*scene)->floor);
	(*scene)->c_rgb = prepare_a_surface((*scene)->ceiling);
	if ((*scene)->f_rgb == NULL || (*scene)->c_rgb == NULL)
		return (-1);
	return (0);
}





/*
ft_split four wall texture lines, with space char as delimiter


ft_split floor/ceiling lines, with comma as delimiter

check if wall texture, that should already start with expected identifier, end with ".xpm"
	

check if 2nd array in ft_split result, for floor / ceiling contains
	3 integers
	each integer's value can only range from 0 to 255, inclusive

int is_details_valid(t_scene *scene)
{


}
*/


/*
int	load_map(char *line, int map_fd)
{


}
*/


/*
ft_split() the line, with ' ' as delimiter
check if ft_split() returns TWO valid (char *) arrays
if arr[0]  == "NO ", and scene->no == NULL
{
	scene->no = ft_strtrim(arr[1], "\n"); // trim the trailing newline, and assign to member in scene struct
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
TO BE RENAMED as load_scene()
# overall:
if invalid/missing/error, return -1; 
	t_scene struct will be freed by caller
	gnl buffer will be flushed, and then fd closed, by callee
else return 0 (success)

# steps:
open file
load scene details
	is_all_six_details_present() // start with expected identifiers
	load_map()
	
is_details_valid()
is_map_valid()

NOTE. if 
*/

int	load_scene_except_map(char *mapfile, t_scene *scene) // TO DO: rename as load_scene
{
	int map_fd;
	
	map_fd = open(mapfile, O_RDONLY);
	if (map_fd == -1)
	{
		ft_putstr_fd("cub3D: Map cannot be opened\n", 2);
		return (-1);
	}
	if (load_scene_details(map_fd, &scene) == -1) // to do: load map()
		return (-1);
	if (prepare_walls(&scene) == -1)
		return (-1);
	
	prepare_floor_ceiling(scene);
	//is_details_valid(scene);
	//is_map_valid(scene>map);
	
	return (0);
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
