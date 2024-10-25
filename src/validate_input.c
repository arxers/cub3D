#include "../inc/cub3D.h"

void	print_scene_struct(t_scene *scene)
{
	printf("\nCurrent state of t_scene struct:\n");
	printf("NO:%s\n", scene->no);
	printf("SO:%s\n", scene->so);
	printf("EA:%s\n", scene->ea);
	printf("WE:%s\n", scene->we);
	printf("F:%s\n", scene->floor);
	printf("C:%s\n", scene->ceiling);
	printf("tmp_map_buf (char *) will begin on next line:\n%s\n", scene->tmp_map_buf);
	printf("map ptr (char **) NOTE. should have empty/newline above: %p\n", scene->map);
	//printf("f_rgb: %p\n", scene->f_rgb);
	//printf("c_rgb: %p\n", scene->c_rgb);
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
	if (s->tmp_map_buf != NULL)
		free(s->tmp_map_buf);
	if (s->map != NULL)
		free_char_map(s->map);
	/*
	if (s->f_rgb != NULL)
		free(s->f_rgb);
	if (s->c_rgb != NULL)
		free(s->c_rgb);
	*/
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
	close(map_fd);
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

/*
checks whether a specific scene detail (char *s), is the first to be loaded into
the t_scene struct

if yes, return (0), for success, 
else return (-1) for failure
*/
int	is_first_detail(char *s, t_scene *scene)
{
	if ( (ft_strncmp(s, "NO ", 3) == 0 && scene->no == NULL) || \
		(ft_strncmp(s, "SO ", 3) == 0 && scene->so == NULL) || \
		(ft_strncmp(s, "EA ", 3) == 0 && scene->ea == NULL) || \
		(ft_strncmp(s, "WE ", 3) == 0 && scene->we == NULL) || \
		(ft_strncmp(s, "F ", 2) == 0 && scene->floor == NULL) || \
		(ft_strncmp(s, "C ", 2) == 0 && scene->ceiling == NULL))
		return (0);
	return (-1);
}

int	assign_f_or_c_to_scene_struct(char *s, t_scene **scene)
{
	if (ft_strncmp(s, "F ", 2) == 0 && (*scene)->floor == NULL)
	{
		(*scene)->floor = ft_strdup(s);
		return (0);	
	}
	else if (ft_strncmp(s, "C ", 2) == 0 && (*scene)->ceiling == NULL)
	{
		(*scene)->ceiling = ft_strdup(s);
		return (0);	
	}
	return (-1);
}

/*
if line starts with expected identifier AND detail is still empty in struct
then assign detail to 'scene' struct

if line starts with expected identifier, BUT detail is already filled in struct
then error out, return (-1)
*/
int	assign_wall_to_scene_struct(char *s, t_scene **scene)
{
	if (ft_strncmp(s, "NO ", 3) == 0 && (*scene)->no == NULL)
	{
		(*scene)->no = ft_strdup(s);
		return (0);
	}
	else if (ft_strncmp(s, "SO ", 3) == 0 && (*scene)->so == NULL)
	{
		(*scene)->so = ft_strdup(s);
		return (0);
	}
	else if (ft_strncmp(s, "EA ", 3) == 0 && (*scene)->ea == NULL)
	{
		(*scene)->ea = ft_strdup(s);
		return (0);	
	}
	else if (ft_strncmp(s, "WE ", 3) == 0 && (*scene)->we == NULL)
	{
		(*scene)->we = ft_strdup(s);
		return (0);	
	}
	return (-1);
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
ft_split, the passed in arg // to discard identifiers at start of line
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
	(*scene)->floor = prepare_a_wall((*scene)->floor);
	(*scene)->ceiling = prepare_a_wall((*scene)->ceiling);
	if ((*scene)->no == NULL || \
		(*scene)->so == NULL || \
		(*scene)->ea == NULL || \
		(*scene)->we == NULL || \
		(*scene)->floor == NULL || \
		(*scene)->ceiling == NULL
		)
		return (-1);
	return (0);
}

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
		return (-1);
}

int	ft_arr_len(char **arr)
{
	int i;
	
	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

/*
accepts a (char *) argument
(char *) argument has to have minimum 1 char, or maximum 3 chars

each char in char array, must be a digit!

convert (char *) to integer
if (i is >= 0 && i <= 255)
	return 0 (success)
else
	return -1 (error)
*/
int	is_valid_rgb_value(char *s)
{
	int i;
	int	len;
	
	len = ft_strlen(s);
	if (len == 0 || len > 3)
		return (-1);
	i = 0;
	while (i < len)
	{
		if (ft_isdigit(s[i]) == 0)
			return (-1);
		i++;
	}
	i = ft_atoi(s);
	if (i >= 0 && i <= 255)
		return (0);
	return (-1);
}


/*
arr = ft_split(), passed in string argument (char *), comma as delimiter 

check if arr:
has ONLY three elements, AND
each element is within the range of zero to 255, inclusive

CHECK #1. ft_split() result, has 3 elements only

CHECK #2. 
for each element in ft_split() result:
convert char array("0" to "255") to int
check if int is between 0 to 255 inclusive

return -1 (error)
else return 0 (success)
*/
int is_valid_rgb_array(char *s)
{
	char 	**arr;
	int		i;
	
	arr = ft_split(s, ',');
	if (!arr)
		return (-1);
	i = ft_arr_len(arr);
	if (i != 3)
	{
		free_char_map(arr);	
		return (-1);
	}
	i = 0;
	while (i < 3)
	{
		if ((is_valid_rgb_value(arr[i])) == -1)
		{
			free_char_map(arr);	
			return (-1);
		}
		i++;
	}
	free_char_map(arr);
	return (0);
}

/*
checks if:
FOUR wall textures, end in ".xpm"
TWO colors, are 3 integers, ranging from 0 to 255 inclusive

if any error, return (-1)
else return (0), success
*/
int is_six_details_valid(t_scene *scene)
{
	if (is_end_with_xpm(scene->no) == -1 || \
		is_end_with_xpm(scene->so) == -1 || \
		is_end_with_xpm(scene->ea) == -1 || \
		is_end_with_xpm(scene->we) == -1)
	{
		ft_putstr_fd("cub3D: Not .xpm extension\n", 2);
		return (-1);
	}	
	if (is_valid_rgb_array(scene->floor) == -1 || \
		is_valid_rgb_array(scene->ceiling) == -1)
	{
		ft_putstr_fd("cub3D: Problematic RGB array value(s)\n", 2);	
		return (-1);
	}	
	return (0);
}

/*
only reach here when prev six details are preliminarily loaded to 'scene' struct

continue to read line by line, with gnl()
NOTE. used safe_strjoin(), instead of ft_strjoin() to sidestep unfreed s1 param
if cannot safe_strjoin() fails:
	print errmsg to stderr
	flush gnl buffer, and close fd
	return -1 (error)
else
	close fd
	return 0 (success)
*/
int	load_map_buffer(char *line, int map_fd, t_scene **scene)
{
	while (line)
	{
		(*scene)->tmp_map_buf = safe_strjoin((*scene)->tmp_map_buf, line);
		if ((*scene)->tmp_map_buf == NULL)
		{
			ft_putstr_fd("cub3D: Cannot load map section)\n", 2);
			flush_gnl(line, map_fd);
			return (-1);
		}
		free(line);
		line = get_next_line(map_fd);
	}	
	close(map_fd);
	return (0);
}


/*
read map.cub line by line, with gnl()
(if) 6 scene details are loaded
	load remainder of map.cub file to a (char *)tmp_map_buf, in 'scene' struct
(if) current line is "empty"
	move to next line
(else if) current line, starts with expected id & is first (not a duplicate)
	then assign detail to t_scene struct
(else)
	err msg, flush_gnl(), return (-1)

*/
int	load_scene_details(int map_fd, t_scene **scene)
{
	char 	*line;

	line = get_next_line(map_fd);
	while (line)
	{
		if (is_all_six_scene_details_present(*scene) == 0)
		{
			if (load_map_buffer(line, map_fd, scene) == -1)
			{
				ft_putstr_fd("cub3D: Cannot load map\n", 2);
				return (-1);			
			}
			return (0);
		}
		if (ft_strcmp(line, "\n") == 0)
		{
			free(line);
			line = get_next_line(map_fd);
			continue ;
		}
		else if (is_start_with_expected_identifier(line) == 0 && \
			is_first_detail(line, *scene) == 0)
		{
			assign_wall_to_scene_struct(line, scene);
			assign_f_or_c_to_scene_struct(line, scene);
		}
		else
		{
			ft_putstr_fd("cub3D: Error in line for scene details\n", 2);
			flush_gnl(line, map_fd);
			return (-1);
		}		
		free(line);
		line = get_next_line(map_fd);
	}
	return (0);
}

/*
NOTE. There are TWO versions of this function:
valid map chars
" \n10NSEW" (mandatory)
" \n10NSEWCDPX" (bonus)

checks tmp_map_buf in scene struct, char by char
if ft_strchr() returns NULL, means it is an invalid char,
	ie. a char NOT found in (char *)ref literal
	then return -1 (error)
else
	return 0 (success)
	
BONUS add 4 chars:
C: Collectible
D: Door
P: Powerloader
X: Xeno
*/
int	is_map_char_valid_bonus(char *s)
{
	int 	i;
	char	ref[] = " \n10NSEWCDPX";
	
	i = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(ref, s[i]) == NULL)
		{
			ft_putstr_fd("cub3D: Invalid map char\n", 2);		
			return (-1);
		}
		i++;	
	}
	return (0);
}

/*
trim away:
leading AND trailing \n in tmp_map_buf
re-assign to scene->tmp_map_buf
*/
int	trim_tmp_map_buf(t_scene **scene)
{
	char	*tmp;
	char	*res;
	
	tmp = (*scene)->tmp_map_buf;
	res = ft_strtrim(tmp, "\n");
	if (!res)
	{
		ft_putstr_fd("cub3D: Problem while preparing map\n", 2);	
		return (-1);
	}
	(*scene)->tmp_map_buf = res;
	free(tmp);
	return (0);
}

/*
accepts a str (tmp_map_buf)
replaces space char, with 1 char, using ft_memset()

NOW, even when there is/are space char(s) in between map lines,
they will show up as 1/wall, 
so the next check, is_tmp_map_buf_split_by_empty_line(), will work
*/
void	replace_space_with_wall(char *s)
{
	int		i;
	
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ')
			ft_memset((void *)&(s[i]), '1', sizeof(char));
		i++;
	}
}

/*
checks if 'big', trimmed tmp_map_buf (char *s), contains 'little ("\n\n")
if ft_strnstr returns non-NULL, means 'little' is found in 'big'
then return -1 (error)
*/
int	is_tmp_map_buf_split_by_empty_line(char *s)
{
	int len;
	
	len = ft_strlen(s);
	if (ft_strnstr(s, "\n\n", len) != NULL)
	{
		ft_putstr_fd("cub3D: empty line found in between map lines\n", 2);	
		return (-1);
	}
	return (0);
}

//# DONE above
//##############################################################################
//# pending below

/*
iterate thru chars in top (zeroth) row,
if any of them are NOT '1', return -1 (error)
*/
int is_toprow_all_walls(char **s)
{
	int i;
	
	i = 0;
	while(s[0][i] != '\0')
	{
		if (s[0][i] != '1')
			return (-1);
		i++;
	}
	return (0);
}

/*
iterate thru chars in bottom row, ie. the row before the last/final NULL ptr
if any of them are NOT '1', return -1 (error)
*/
int	is_botrow_all_walls(char **s)
{
	int	i;
	int	j;
	
	i = 0;
	while (s[i + 1] != NULL)
		i++;
	j = 0;
	while (s[i][j] != '\0')
	{
		if (s[i][j] != '1')
			return (-1);
		j++;
	}
	return (0);
}

/* 
checks if left col of rectangular map, consists of only wall chars
if any of them are NOT '1', return -1 (error)
*/
int is_lcol_all_walls(char **s)
{
	int	i;
	
	i = 0;
	while(s[i] != NULL)
	{
		if(s[i][0] != '1')
			return (-1);
		i++;
	}
	return (0);
}

/* 
checks if char, before the \0 char, consists of only wall chars
if any of them are NOT '1', return -1 (error)

NOTE. does not guarantee/ensure map is rectangular!
*/
int is_rcol_all_walls(char **s)
{
	int i;
	int	j;
	
	i = 0;
	while (s[i] != NULL)
	{
		j = 0;
		while (s[i][j + 1] != '\0')
			j++;
		if (s[i][j] != '1')
			return (-1);
		i++;
	}
	return (0);
}

/*
check if all 4 sides of rectangular map, consists of only wall chars

check top row
check bot row
check lcol
check rcol
*/
int	is_map_surrounded_by_walls(char **s)
{
	if ((is_toprow_all_walls(s) == -1) || \
		(is_botrow_all_walls(s) == -1) || \
		(is_lcol_all_walls(s) == -1) || \
		(is_rcol_all_walls(s) == -1 ))
	{
		ft_putstr_fd("cub3D: Map is NOT surrounded by walls\n", 2);
		return (-1);
	}
	return (0);
}

/*
AFTER passing is_map_char_valid()

tmp_map_buf may contain:
	empty_lines before start of map
	empty lines in between map lines ie. \n\n
	empty lines after end of map

to do:
trim leading newlines, before start of map
trim trailing newlines, after end of map
re-assign trimmed tmp_map_buf to scene->tmp_map_buf 
ft_strtrim() ?


check if there are empty lines in between, map lines
use ft_strnstr() to see if "little" is found in "big"
where big is tmp_map_buf
where little is "\n\n", 

ft_split(tmp_map_buf), using \n as delimiter char
assign result of ft_split() to scene->map // (char **)
*/



/*
# overall:
if invalid/missing/error, return -1; 
	t_scene struct will be freed by caller
	gnl buffer will be flushed, and then fd closed, by callee
else return 0 (success)

# steps:
open file
load scene details
	is_all_six_details_present() // start with expected identifiers
	load_map_buffer() // currently, called in load_scene_details()

	!!! RESTART HERE, last updated 23 Oct 2024 !!!
	
	prepare_map() 
		check if map only contains valid chars
		check if map contains emptyline ("\n\n")
		ft_split(char *tmp_map_buf), using \n as delimiter
		assign (char **) result of ft_split() to t_scene struct
		is_map_valid() // check pdf etc...
		milestone, done? OMG!
*/

int	load_scene(char *mapfile, t_scene *scene) // TO DO: rename as load_scene
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
	if (is_six_details_valid(scene) == -1)
		return (-1);
	if (is_map_char_valid_bonus(scene->tmp_map_buf) == -1)
		return (-1);
	if (trim_tmp_map_buf(&scene) == -1)
		return (-1);
	replace_space_with_wall(scene->tmp_map_buf);
	if (is_tmp_map_buf_split_by_empty_line(scene->tmp_map_buf) == -1)
		return (-1);
	scene->map = ft_split(scene->tmp_map_buf, '\n');	
	if (is_map_surrounded_by_walls(scene->map) == -1)
		return (-1);
		
	// is map minimum 3 by 3 
	// is_map_valid(scene>map);
	//close(map_fd);
	return (0);
}
	

/*
MISC NOTES...


# load_map()
continue reading remainder of map.cub file (via map_fd), via gnl(), line by line

join line, by line, into a single long (char *), use ft_strjoin()

check if (char *) contains any invalid chars

valid chars: 
' ', space 
'\n', newline
'1', one
'0', zero
'N', north
'S', south
'E', east
'W', west

# is_map_valid()
CHECK #1.
if ft_strchr() returns NULL, means some char, not in valid chars, was found in buffer

CHECK #2.
if "\n\n" means empty line found in map, return -1 (error)

# prepare_map() // convert map from (char *) to (char **)
ft_split(char * line), using '\n' as delimiter char

CHECK #3.
min num of rows == 3
min num of cols == 3
else return -1 (error)

COUNT:
max_width, num of cols
max_length, num of rows
to alloc space on heap, for final valid map

replace ' '/spaces in (char **) map with ? char?

flood fill from player position
if leak, then return -1 (error)

thanks to @jolai for spotting the error
get_next_line(map_fd); // logic error, not assigning return value !?
line = get_next_line(map_fd); // solution... LOL
*/

/*
int is_map_valid(char **map)
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

// if all seven scene details are present,
// ft_split the map in a single line, into a (char **), using '\n' as delimiter
// free the (char *) singleline map

