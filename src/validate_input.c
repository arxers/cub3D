/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:20:28 by jsu               #+#    #+#             */
/*   Updated: 2024/11/01 17:47:22 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/validate_input.h"

void	print_2d_map(char **s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] != NULL)
	{
		j = 0;
		while (s[i][j] != '\0')
		{
			write(1, &(s[i][j]), 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void	print_scene_struct(t_scene *scene)
{
	printf("\nCurrent state of t_scene struct:\n");
	printf("NO:%s\n", scene->no);
	printf("SO:%s\n", scene->so);
	printf("EA:%s\n", scene->ea);
	printf("WE:%s\n", scene->we);
	printf("F:%s\n", scene->floor);
	printf("hex_floor:%x\n", scene->hex_floor);
	printf("C:%s\n", scene->ceiling);
	printf("hex_ceiling:%x\n", scene->hex_ceiling);
	printf("tmp_map_buf (char *) begin on next line:\n%s\n", scene->tmp_map_buf);
	printf("map ptr (char **): %p\n", scene->map);
	print_2d_map(scene->map);
	printf("map_bak ptr (char **): %p\n", scene->map_bak);
	print_2d_map(scene->map_bak);
	printf("map_width: %d\n", scene->map_dim.x);
	printf("map_height: %d\n", scene->map_dim.y);
	printf("pos_player.x: %d\n", scene->p_pos.x);
	printf("pos_player.y: %d\n", scene->p_pos.y);
	printf("pos_xeno.x: %d\n", scene->pos_xeno.x);
	printf("pos_xeno.y: %d\n", scene->pos_xeno.y);
	printf("pos_powerloader.x: %d\n", scene->pos_powerloader.x);
	printf("pos_powerloader.y: %d\n", scene->pos_powerloader.y);
}

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	printf("print_arr() eg. result of ft_split()\n");
	while (arr[i] != NULL)
	{
		printf("%d: %s\n", i, arr[i]);
		i++;
	}
}

void	flush_gnl(char **line, int map_fd)
{
	if (*line)
		free(*line);
	get_next_line(-1);
	close(map_fd);
	*line = NULL;
}

void	free_char_map(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/*
for t_scene struct,
checks if alloc~ed elements are present, and if so, free() them!

NOTE. no need to free() the t_scene elements that are NOT alloc~ed
*/
void	free_scene_struct(t_scene *s)
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
	if (s->map_bak != NULL)
		free_char_map(s->map_bak);
}

/* 
check num of cmdline args
if argc != 2, return -1 (error)
else return 0
*/
int	check_n_cmdline_args(int ac)
{
	if (ac != 2)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		ft_putstr_fd("Error\nUsage: cub3D [*.cub]\n", 2);
		return (-1);
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
		ft_putstr_fd("Error\nMap does not end in .cub\n", 2);
		return (-1);
	}
}

/*
if file can be opened, then return 0
else return -1
*/
int	is_map_file_openable(char *mapfile)
{
	int	map_fd;

	map_fd = open(mapfile, O_RDONLY);
	if (map_fd == -1)
	{
		ft_putstr_fd("Error\nMap cannot be opened\n", 2);
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
		|| !ft_strncmp(s, "C ", 2))
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
	if ((ft_strncmp(s, "NO ", 3) == 0 && scene->no == NULL) || \
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
ft_split the line that begins with the expected identifiers at start of line
replace the last char, should be a '\n' char, with '\0'
this will handle the case where ft_split "xxx"<space>'\n', returns 3 rows

ensure that the ft_split result only has 2 rows! with ft_count_strings()
ft_strdup, the second array from the ft_split result
	
credits to @filim, for helping me "over the hump"!
*/
char	*prepare_a_wall(char *s)
{
	char	**arr;
	char	*tmp;

	s[ft_strlen(s) - 1] = '\0';
	arr = ft_split(s, ' ');
	if (!arr)
		return (NULL);
	free(s);
	if (ft_count_strings(arr) != 2)
	{
		free_char_map(arr);	
		return (NULL);
	}
	tmp = ft_strdup(arr[1]);
	if (!tmp)
		return (NULL);
	free_char_map(arr);
	// res = ft_strtrim(tmp, "\n");
	// if (!res)
	// 	return (NULL);
	// free(tmp);
	return (tmp);
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
		(*scene)->ceiling == NULL)
		{
			ft_putstr_fd("Error\nProblem with scene details\n", 2);
			return (-1);
		}
	return (0);
}

// ft_strcmp(&(s1[len - 4]), ".xpm")
int	is_end_with_xpm(char *s)
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

// int	ft_arr_len(char **arr)
// {
// 	int	i;

// 	i = 0;
// 	while (arr[i] != NULL)
// 		i++;
// 	return (i);
// }

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
	int	i;
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

int	ft_count_char(char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count);
}

/*
ft_split() the line, that starts with the expected identifier 'F'/'C'

CHECK #1. count the number of comma chars in the line

CHECK #2. ft_split() result, should only have 3 rows

CHECK #3. for each element in ft_split() result:
convert char array to int
check if int is between 0 to 255 inclusive
*/
int	is_valid_rgb_array(char *s)
{
	char	**arr;

	if (ft_count_char(s, ',') != 2)
		return (-1);
	arr = ft_split(s, ',');
	if (!arr)
		return (-1);
	if (ft_count_strings(arr) != 3
		|| is_valid_rgb_value(arr[0]) == -1
		|| is_valid_rgb_value(arr[1]) == -1
		|| is_valid_rgb_value(arr[2]) == -1)
	{
		free_char_map(arr);
		return (-1);
	}
	free_char_map(arr);
	return (0);
}

/*
converts an assumed VALID (char *) rgb array, eg. "0,42,255",
to an unsigned int, and returns this value
returns -1 (error)
*/
int	convert_rgb_array_to_int(char *s)
{
	int				r;
	int				g;
	int				b;
	char			**arr;

	arr = ft_split(s, ',');
	if (!arr)
		return (-1);
	r = ft_atoi(arr[0]);
	g = ft_atoi(arr[1]);
	b = ft_atoi(arr[2]);
	free_char_map(arr);
	return ((r << 16) | (g << 8) | b);
}

/*
checks if:
FOUR wall textures, end in ".xpm"
TWO colors, are 3 integers, ranging from 0 to 255 inclusive

if any error, return (-1)
else return (0), success
*/
int	is_six_details_valid(t_scene *scene)
{
	if (is_end_with_xpm(scene->no) == -1 || \
		is_end_with_xpm(scene->so) == -1 || \
		is_end_with_xpm(scene->ea) == -1 || \
		is_end_with_xpm(scene->we) == -1)
	{
		ft_putstr_fd("Error\nWall texture file not .xpm extension\n", 2);
		return (-1);
	}	
	if (is_valid_rgb_array(scene->floor) == -1 || \
		is_valid_rgb_array(scene->ceiling) == -1)
	{
		ft_putstr_fd("Error\nProblematic RGB array value\n", 2);
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
			ft_putstr_fd("Error\nCannot load map section)\n", 2);
			flush_gnl(&line, map_fd);
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

int	load_scene_details_to_struct(char **line, int map_fd, t_scene **scene)
{
	if (ft_strcmp(*line, "\n") == 0)
	{
		free(*line);
		*line = get_next_line(map_fd);
		return (1);
	}
	else if (is_start_with_expected_identifier(*line) == 0 && \
		is_first_detail(*line, *scene) == 0)
	{
		assign_wall_to_scene_struct(*line, scene);
		assign_f_or_c_to_scene_struct(*line, scene);
		return (0);
	}
	else
	{
		ft_putstr_fd("Error\nProblem with line for scene details\n", 2);
		flush_gnl(line, map_fd);
		return (-1);
	}		
}

int	load_scene_details(int map_fd, t_scene **scene)
{
	char	*line;
	int		res;

	line = get_next_line(map_fd);
	while (line)
	{
		if (is_all_six_scene_details_present(*scene) == 0)
		{
			if (load_map_buffer(line, map_fd, scene) == -1)
			{
				ft_putstr_fd("Error\nCannot load map\n", 2);
				return (-1);
			}
			return (0);
		}
		res = load_scene_details_to_struct(&line, map_fd, scene);
		if (res == 1)
			continue ;
		else if (res == -1)
			return (-1);
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
	const char	ref[] = " \n10NSEWCDPX";
	int			i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(ref, s[i]) == NULL)
		{
			ft_putstr_fd("Error\nInvalid map char\n", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	is_map_char_valid_mandatory(char *s)
{
	const char	ref[] = " \n10NSEW";
	int			i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(ref, s[i]) == NULL)
		{
			ft_putstr_fd("Error\nInvalid map char\n", 2);
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
		ft_putstr_fd("Error\nProblem while preparing map\n", 2);
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
they will show up as 0/zeroes
so the next check, is_tmp_map_buf_split_by_empty_line(), will work
*/
void	replace_space_with_zero(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ')
			ft_memset((void *)&(s[i]), '0', sizeof(char));
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
	int	len;

	len = ft_strlen(s);
	if (ft_strnstr(s, "\n\n", len) != NULL)
	{
		ft_putstr_fd("Error\nEmpty line found in between map lines\n", 2);
		return (-1);
	}
	return (0);
}

/*
calculates the map's dimensions
and assign the values to map_width & map_height, in 'scene' struct
*/
void	count_map_area(char **map_temp, t_scene *scene)
{
	t_point	index;
	int		count;
	int		max_x;

	count = 0;
	max_x = 0;
	index.y = 0;
	while (map_temp[index.y])
	{
		index.x = 0;
		count = 0;
		while (map_temp[index.y][index.x])
		{
			count++;
			index.x++;
		}
		if (count > max_x)
			max_x = count;
		index.y++;
	}
	scene->map_dim.x = max_x;
	scene->map_dim.y = index.y;
}

/*
accepts a (char **)tmp_map, and ptr to scene struct
callocs space for (char **) for scene->map
*/
int	init_map_array(char ***map, char **map_temp, t_scene *scene)
{
	t_point	index;

	count_map_area(map_temp, scene);
	*map = ft_calloc(scene->map_dim.y + 1, sizeof(char *));
	if (!*map)
		return (-1);
	index.y = 0;
	while (index.y < scene->map_dim.y)
	{
		(*map)[index.y] = ft_calloc (scene->map_dim.x + 1, sizeof(char));
		if (!(*map)[index.y])
			return (-1);
		ft_memset((*map)[index.y], '0', scene->map_dim.x);
		index.y++;
	}
	return (0);
}

/*
accepts a (char **)tmp_map, and ptr to scene struct
callocs space for (char **) for scene->map_bak
*/
// int	init_map_bak_array(char **map_temp, t_scene *scene)
// {
// 	t_point	index;

// 	count_map_area(map_temp, scene);
// 	scene->map_bak = ft_calloc(scene->map_dim.y + 1, sizeof(char *));
// 	if (!scene->map_bak)
// 		return (-1);
// 	index.y = 0;
// 	while (index.y < scene->map_dim.y)
// 	{
// 		scene->map_bak[index.y] = ft_calloc(scene->map_dim.x + 1, sizeof(char));
// 		if (!scene->map_bak[index.y])
// 			return (-1);
// 		index.y++;
// 	}
// 	index.y = 0;
// 	while (scene->map_bak[index.y])
// 	{
// 		index.x = 0;
// 		while (index.x < scene->map_dim.x)
// 		{
// 			scene->map_bak[index.y][index.x] = '0';
// 			index.x++;
// 		}
// 		index.y++;
// 	}
// 	return (0);
// }

/*
copy data from src, (char **)tmp map
to scene->map
*/
void	load_map_data(char **s, t_scene *scene)
{
	char	**dst;
	int		i;
	int		j;
	int		len;

	dst = scene->map;
	i = 0;
	while (s[i] != NULL)
	{
		j = 0;
		len = ft_strlen(s[i]);
		while (j < len)
		{
			dst[i][j] = s[i][j];
			j++;
		}
		i++;
	}
}

/*
copy data from src, (char **)tmp map
to dst: scene->map_bak
*/
void	load_map_bak_data(char **s, t_scene *scene)
{
	char	**dst;
	int		i;
	int		j;
	int		len;

	dst = scene->map_bak;
	i = 0;
	while (s[i] != NULL)
	{
		j = 0;
		len = ft_strlen(s[i]);
		while (j < len)
		{
			dst[i][j] = s[i][j];
			j++;
		}	
		i++;
	}
}

/*
returns the count of chars 'ch' found in (char **)map
*/
int	count_char_in_map(char **map, char ch)
{
	int	i;
	int	j;
	int	res;

	res = 0;
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == ch)
				res += 1;
			j++;
		}
		i++;
	}
	return (res);
}

/*
wrapper for count_char_in_map()

scan the map, and count the number of valid player chars
if sum total of valid player char is NOT one, return -1 (error)
else return 0 (success) 
*/
int	is_num_player_valid(char **map)
{
	int	num_n;
	int	num_s;
	int	num_e;
	int	num_w;

	num_n = count_char_in_map(map, 'N');
	num_s = count_char_in_map(map, 'S');
	num_e = count_char_in_map(map, 'E');
	num_w = count_char_in_map(map, 'W');
	if (num_n + num_s + num_e + num_w != 1)
	{
		ft_putstr_fd("Error\nIncorrect number of PLAYER char in map\n", 2);
		return (-1);
	}
	return (0);
}

int	is_num_xeno_valid(char **map)
{
	int	num_enemy;

	num_enemy = count_char_in_map(map, 'X');
	if (num_enemy != 1)
	{
		ft_putstr_fd("Error\nIncorrect number of ENEMY char in map\n", 2);
		return (-1);
	}
	return (0);
}

int	is_num_powerloader_valid(char **map)
{
	int	num_armor;

	num_armor = count_char_in_map(map, 'P');
	if (num_armor != 1)
	{
		ft_putstr_fd("Error\nIncorrect number of ARMOR char in map\n", 2);
		return (-1);
	}
	return (0);
}

int	is_num_collectibles_valid(char **map)
{
	int	num_collectible;

	num_collectible = count_char_in_map(map, 'C');
	if (num_collectible < REQUIRED_ITEMS)
	{
		ft_putstr_fd("Error\nIncorrect number of COLLECTIBLE char in map, ", 2);
		ft_putstr_fd("expected ", 2);
		ft_putnbr_fd(REQUIRED_ITEMS, 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	return (0);
}

/*
set a tmp (char *) ptr to the TOP row of map
iterate thru chars in the row,
if fill char 'F' found, return 0 (success)
else return -1 (failure)
*/
int	is_fill_char_at_toprow(t_scene *s)
{
	int		i;

	i = 0;
	while (s->map_bak[0][i] != '\0')
	{
		if (s->map_bak[0][i] == 'F')
			return (0);
		i++;
	}
	return (-1);
}

/*
set a tmp (char *) ptr to the BOTTOM row of map
iterate thru chars in the row,
if fill char 'F' found, return 0 (success)
else return -1 (failure)
*/
int	is_fill_char_at_botrow(t_scene *s)
{
	int		i;

	i = 0;
	while (s->map_bak[s->map_dim.y - 1][i] != '\0')
	{
		if (s->map_bak[s->map_dim.y - 1][i] == 'F')
			return (0);
		i++;
	}
	return (-1);
}

/*
iterate thru rows in the map
if fill char 'F' found in LEFT col, return 0 (success)
else return -1 (failure)
*/
int	is_fill_char_at_lcol(t_scene *s)
{
	int	i;

	i = 0;
	while (s->map_bak[i] != NULL)
	{
		if (s->map_bak[i][0] == 'F')
			return (0);
		i++;
	}
	return (-1);
}

/*
iterate thru rows in the map
if fill char 'F' found in RIGHT col, return 0 (success)
else return -1 (failure)
*/
int	is_fill_char_at_rcol(t_scene *s)
{
	int	i;

	i = 0;
	while (s->map_bak[i] != NULL)
	{
		if (s->map_bak[i][s->map_dim.x - 1] == 'F')
			return (0);
		i++;
	}
	return (-1);
}

/*
If a fill char is found in any border side of the map,
then return 0 (success) 

NOTE. If there is a fill char at the map's border. REJECT the map
*/
int	is_fill_char_at_map_border(t_scene *s)
{
	if ((is_fill_char_at_toprow(s) == 0) || \
		(is_fill_char_at_botrow(s) == 0) || \
		(is_fill_char_at_lcol(s) == 0) || \
		(is_fill_char_at_rcol(s) == 0))
	{
		ft_putstr_fd("Error\nFlood fill char found at border wall\n", 2);
		return (0);
	}
	return (-1);
}

/*
NOTE. ff is short for flood fill

if out of bounds row-wise, return
if out of bounds col-wise, return
if char at current pos: is wall '1', or fill 'F', return
if char at current pos: is empty '0', or valid (player) char, replace with 'F'
try to ff() the four cardinal directions, relative to current char pos
*/
void	ff_mandatory(int i, int j, t_scene *s)
{
	if (i < 0 || i > s->map_dim.y - 1)
		return ;
	if (j < 0 || j > s->map_dim.x - 1)
		return ;
	if (s->map_bak[i][j] == '1' || s->map_bak[i][j] == 'F')
		return ;
	if (s->map_bak[i][j] == '0' || ft_strchr("NSEW", s->map_bak[i][j]))
		s->map_bak[i][j] = 'F';
	ff_mandatory(i + 1, j, s);
	ff_mandatory(i - 1, j, s);
	ff_mandatory(i, j + 1, s);
	ff_mandatory(i, j - 1, s);
}

/*
same as mandatory version
only difference is first arg for ft_strchr() includes 4 extra chars: C D X P
*/
void	ff_bonus(int i, int j, t_scene *s)
{
	if (i < 0 || i > s->map_dim.y - 1)
		return ;
	if (j < 0 || j > s->map_dim.x - 1)
		return ;
	if (s->map_bak[i][j] == '1' || s->map_bak[i][j] == 'F')
		return ;
	if (s->map_bak[i][j] == '0' || ft_strchr("NSEWCDXP", s->map_bak[i][j]))
		s->map_bak[i][j] = 'F';
	ff_bonus(i - 1, j, s);
	ff_bonus(i + 1, j, s);
	ff_bonus(i, j - 1, s);
	ff_bonus(i, j + 1, s);
}

/*
returns 0 (success) after finding the first occurrence of a valid PLAYER char,
'N'/'S'/'E'/'W'
SIDE EFFECT: load its coordinates into (t_point) scene->pos_player
*/
int	load_player_pos(char **map, t_scene *scene)
{
	int		i;
	int		j;
	char	*player;

	player = "NSEW";
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (ft_strchr(player, map[i][j]))
			{
				scene->p_pos.x = j;
				scene->p_pos.y = i;
				return (0);
			}
			j++;
		}
		i++;
	}
	ft_putstr_fd("Error\nPLAYER char missing from map\n", 2);
	return (-1);
}

/*
returns 0 (success) after finding the first occurrence of a valid ENEMY char, 'X'
SIDE EFFECT: load coordinates into (t_point) scene->pos_xeno
*/
int	load_xeno_pos(char **map, t_scene *scene)
{
	int		i;
	int		j;
	char	*enemy;

	enemy = "X";
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (ft_strchr(enemy, map[i][j]))
			{
				scene->pos_xeno.x = j;
				scene->pos_xeno.y = i;
				return (0);
			}
			j++;
		}
		i++;
	}
	ft_putstr_fd("Error\nENEMY char missing from map\n", 2);
	return (-1);
}

/*
returns 0 (success) after finding the first occurrence of a valid ENEMY char, 'X'
SIDE EFFECT: load coordinates into (t_point) scene->pos_xeno
*/
int	load_powerloader_pos(char **map, t_scene *scene)
{
	int		i;
	int		j;
	char	*armor;

	armor = "P";
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (ft_strchr(armor, map[i][j]))
			{
				scene->pos_powerloader.x = j;
				scene->pos_powerloader.y = i;
				return (0);
			}
			j++;
		}
		i++;
	}
	ft_putstr_fd("Error\nARMOR char missing from map\n", 2);
	return (-1);
}

//# DONE above
//##############################################################################
//# pending below

/* 
IMPT! for bonus implementation
need to replace TWO functions, in load_scene()

#1:
replace, is_map_char_valid_mandatory(),
with, is_map_char_valid_bonus()

#2:
replace, ff_mandatory(),
with, ff_bonus()

key difference is that in the bonus versions, they consider FOUR extra chars:
C, D, X, P
*/
int	load_scene(char *mapfile, t_scene *scene)
{
	int		map_fd;
	char	**tmp;

	map_fd = open(mapfile, O_RDONLY);
	if (map_fd == -1)
	{
		ft_putstr_fd("Error\nMap cannot be opened\n", 2);
		return (-1);
	}
	if (load_scene_details(map_fd, &scene) == -1 || prepare_walls(&scene) == -1
		|| is_six_details_valid(scene) == -1)
		return (-1);
	scene->hex_floor = convert_rgb_array_to_int(scene->floor);
	scene->hex_ceiling = convert_rgb_array_to_int(scene->ceiling);
	if (is_map_char_valid_bonus(scene->tmp_map_buf) == -1)
		return (-1);
	if (trim_tmp_map_buf(&scene) == -1)
		return (-1);
	replace_space_with_zero(scene->tmp_map_buf);
	if (is_tmp_map_buf_split_by_empty_line(scene->tmp_map_buf) == -1)
		return (-1);
	tmp = ft_split(scene->tmp_map_buf, '\n');
	if (!tmp)
	{
		ft_putstr_fd("Error\nProblem with ft_split tmp_map_buf\n", 2);
		return (-1);
	}
	if (init_map_array(&scene->map, tmp, scene) == -1 || \
		init_map_array(&scene->map_bak, tmp, scene) == -1)
	{
		ft_putstr_fd("Error\nmalloc for map, fail\n", 2);
		return (-1);
	}
	load_map_data(tmp, scene);
	load_map_bak_data(tmp, scene);
	free_char_map(tmp);
	if (is_num_player_valid(scene->map) == -1
		|| load_player_pos(scene->map, scene) == -1
		|| is_num_xeno_valid(scene->map) == -1
		|| load_xeno_pos(scene->map, scene) == -1
		|| is_num_powerloader_valid(scene->map) == -1
		|| load_powerloader_pos(scene->map, scene) == -1
		|| is_num_collectibles_valid(scene->map) == -1)
		return (-1);
	ff_bonus(scene->p_pos.y, scene->p_pos.x, scene);
	if (is_fill_char_at_map_border(scene) == 0)
		return (-1);
	return (0);
}

/*
to do 01 Nov 2024

# refactor load_scene(), function has >25 lines 

# split functions in validate_input.c into separate .c files
*/