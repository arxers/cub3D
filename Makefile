NAME = cub3D
CFLAGS = -Wall -Wextra -Werror
SRC =   src/main.c
OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a
LIBFT_FLAGS = -Llibft -lft
MLXDIR = mlx
MLX_URL = https://github.com/42Paris/minilibx-linux
MLX = $(MLXDIR)/libmlx.a
MLX_FLAGS = -I$(MLXDIR) -L$(MLXDIR) -lXext -lX11
LIBRARY = $(LIBFT) $(MLX)
LIBRARY_FLAGS = $(LIBFT_FLAGS) $(MLX_FLAGS) -lm

all: $(NAME)

$(MLXDIR)/Makefile:
	@if [ ! -d $(MLXDIR) ]; then \
		git clone $(MLX_URL) $(MLXDIR); \
	fi

$(MLX): $(MLXDIR)/Makefile
	make -C $(MLXDIR)

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	cc $(CFLAGS) $(OBJ) $(LIBRARY) $(LIBRARY_FLAGS) -o $(NAME)

libft/libft.a:
	make $(LIBFLAG) -C libft

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C libft clean
	make -C $(MLXDIR) clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean
	rm -rf $(MLXDIR)

re: fclean all

debug: CFLAGS += -g
debug: LIBFLAG += debug
debug: re

gdb: debug
	gdb -tui ./$(NAME)

valgrind: debug
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re debug gdb valgrind