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


// PAUSED 16 Oct 2024
/*
if reading the map.cub part-way, 
need to finish reading the file / flush the gnl buffer
close the file/file descriptor
*/


/*
try to load 6 lines into t_scene struct
will only return 0, when all 6 scene details are present in t_scene struct
else return -1 (error)

HOW?
read .cub file, line by line, using get_next_line()
skip past lines, containing just a single '\n' char
once the 6 lines in the t_scene struct are populated, return 0
 
NOTE. 
line returned from GNL, contains "\n\0"
final line returned by GNL, may contain "\n\0", or "\0"
*/
int	load_scene_details(int map_fd, t_scene **scene)
{
	char 	*line;

	line = get_next_line(map_fd);
	while (line)
	{
		if (is_all_six_scene_details_present(*scene) == 1)	
			return (0);
		else if (ft_strcmp(line, "\n") == 0)
		{
			free(line);
			line = get_next_line(map_fd);
			continue ;
		}
		else if (is_start_with_expected_identifier(line) == 1)
			assign_detail_to_scene_struct(line, scene);
		else
		{
			ft_putstr_fd("cub3D: Invalid/missing line for scene details\n", 2);
			break ;
		}
		free(line);
		line = get_next_line(map_fd);
	}
	return (-1);
}

//# DONE above
//##############################################################################
//# pending below

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
if all 6 details are valid, return 1; else return 0

REMB. 
load_scene_details() already guarantees that the the details in scene struct
already starts w/ an expected identifier, eg. "NO ", "SO ", ... "F ", "C " etc

for wall texture, is_scene_details_valid():
if "NO ", "SO "..., line in scene struct, ends with .xpm
	then, arr = ft_split(scene->no) with ' '/space as delimiter
	re-assign arr[1], ???.xpm to scene struct
if "F ..."/"C ..." line in scene struct, ft_split


int	is_scene_details_valid(t_scene *scene)
{
	
 //pass

}
*/

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
		return (-1);
	
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
