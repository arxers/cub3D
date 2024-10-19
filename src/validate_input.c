#include "../inc/cub3D.h"

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
		//(*scene)->no = ft_strdup(ft_strtrim(s, "\n"));
		(*scene)->no = ft_strdup(s);
	else if (ft_strncmp(s, "SO ", 3) == 0 && (*scene)->so == NULL)
		//(*scene)->so = ft_strdup(ft_strtrim(s, "\n"));
		(*scene)->so = ft_strdup(s);
	else if (ft_strncmp(s, "EA ", 3) == 0 && (*scene)->ea == NULL)
		//(*scene)->ea = ft_strdup(ft_strtrim(s, "\n"));
		(*scene)->ea = ft_strdup(s);
	else if (ft_strncmp(s, "WE ", 3) == 0 && (*scene)->we == NULL)
		//(*scene)->we = ft_strdup(ft_strtrim(s, "\n"));
		(*scene)->we = ft_strdup(s);
	else if (ft_strncmp(s, "F ", 2) == 0 && (*scene)->floor == NULL)
		//(*scene)->floor = ft_strdup(ft_strtrim(s, "\n"));
		(*scene)->floor = ft_strdup(s);
	else if (ft_strncmp(s, "C ", 2) == 0 && (*scene)->ceiling == NULL)
		//(*scene)->ceiling = ft_strdup(ft_strtrim(s, "\n"));
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

//# DONE above
//##############################################################################
//# pending below

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
	printf("map ptr: %p\n", scene->map);
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
handle 6 scene details, broken down into several steps
if error at any step, return -1
else return 0

open the ".cub" file
load scene details. 

*/
int	load_scene_except_map(char *mapfile, t_scene *scene)
{
	int map_fd;
	
	map_fd = open(mapfile, O_RDONLY);
	if (map_fd == -1)
	{
		ft_putstr_fd("cub3D: Map cannot be opened\n", 2);
		return (-1);
	}
	
	if (load_scene_details(map_fd, &scene) == -1)
	{
		//print_scene_struct(scene);
		//free_scene_struct(scene);
		//print_scene_struct(scene);
		return (-1);
	}
	//if (is_all_six_scene_details_present(scene) == -1)
	//	return (-1);
	//is_scene_details_valid(scene);

	// first map line, is line after texture line, that is not just newline
	// last map line, is the line before the first newline
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
