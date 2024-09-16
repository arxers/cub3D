/*
function, to_int_array(), converts a (char *) into (int *)

Wrapping the function thus allows the conversion of a (char **) to a (int **)

Q: Why do we need this function?
A: Because map.cub accepts a text file, 
	but @jaslim's cub3D code works with a int ** map
*/

#include <unistd.h> // write()
#include <string.h> // strlen()
#include <stdio.h> // printf()
#include <stdlib.h> // malloc(), free()


int	ft_putchar(char ch)
{
	int res;
	
	res = write(1, &ch, 1);
	return (res);
}

void	ft_putnbr(int n)
{
	long int	long_n;

	long_n = n;
	if (long_n < 0)
	{
		ft_putchar('-');
		long_n = -long_n;
	}
	if (long_n <= 9)
		ft_putchar(long_n + '0');
	else
	{
		ft_putnbr(long_n / 10);
		ft_putnbr(long_n % 10);
	}
}

void	print_char_map(char **map)
{
	int	i;
	int	j;
	
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			ft_putchar(map[i][j]);
			ft_putchar('\t');
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

/* 
NOTE. because int ** is NOT null terminated, 
we have to set limits based on row height, and col width!
*/ 
void	print_int_map(int **map)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < 6)
	{
		j = 0;
		while (j < 6)
		{
			ft_putnbr(map[i][j]);
			ft_putchar('\t');
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

/*
for cub3D

IMPT!
Caller is responsible for freeing the (int *), 
that is malloc~ed by this function.

Returns a (int *) containing the converted ints (from chars)

Currently converts:
chars 0, 1, N, S, E, W to 
ints 0, 1, 78, 83, 69, 87
*/
int	*to_int_array(char *s)
{
	int	a_len;
	int	*new;
	int	i;
	
	a_len = strlen(s); // to do, replace with ft_strlen
	new = malloc(sizeof(int) * a_len);
	if (!new)
		return (NULL);
	i = 0;
	while (i < a_len)
	{
		if (s[i] == '0')
			new[i] = 0;
		else if (s[i] == '1')
			new[i] = 1;
		else if (s[i] == 'N')
			new[i] = 78;
		else if (s[i] == 'S')
			new[i] = 83;
		else if (s[i] == 'E')
			new[i] = 69;
		else if (s[i] == 'W')
			new[i] = 87;
		i++;
	}
	return (new);
}
int	main(void)
{
	//char	test[] = {'0', '1', 'N', 'S', 'E', 'W', '\0'};
	
	char	r0[] = {'1', '1', '1', '1', '1', '1', '\0'};
	char	r1[] = {'1', '0', '1', '0', '0', '1', '\0'};
	char	r2[] = {'1', '0', '1', '0', '0', '1', '\0'};
	char	r3[] = {'1', '0', '1', '1', '0', '1', '\0'};
	char	r4[] = {'1', 'N', 'S', 'E', 'W', '1', '\0'};
	char	r5[] = {'1', '1', '1', '1', '1', '1', '\0'};

	char	*test[] = {r0, r1, r2, r3, r4, r5, NULL};
	
	print_char_map(test);

	// assume we already know the num of rows and cols for (int **)
	int	**new;
	int i;
	
	new = malloc(sizeof(int *) * 6); // int ** is NOT null terminated!
	i = 0;
	while (test[i] != NULL)
	{
		new[i] = to_int_array(test[i]);
		i++;
	}
	
	printf("\n\n");	
	print_int_map(new);
		
	// to do, remember to free!!!
	// char **, and enclosed char *
	// int **, and enclosed int *

	return (0);
}
