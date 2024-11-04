NAME = cub3D
CFLAGS = -Wall -Wextra -Werror
SRC =   src/main.c src/validate_input.c src/cleanup.c \
		src/init_game.c src/init_game_utils.c src/init_image.c src/init_map.c \
		src/background.c \
		src/key_hooks.c src/key_specials.c src/mouse_event.c \
		src/image_utils.c src/image_pixel_utils.c src/image_primitives.c src/image_copy_paste.c \
		src/minimap.c \
		src/enemy_hunt.c src/enemy_chase.c src/enemy_render.c \
		src/player_movement.c src/player_look.c src/player_utils.c \
		src/display_ui.c src/interact.c \
		src/raycasting.c src/dda.c src/dda_special.c \
		src/pwl_render.c src/item.c \
		src/utils.c
OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a
LIBFT_FLAGS = -Llibft -lft
MLXDIR = mlx
MLX_URL = https://github.com/42Paris/minilibx-linux
MLX = $(MLXDIR)/libmlx.a
MLX_FLAGS = -L$(MLXDIR) -lXext -lX11
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

fsanitize: CFLAGS += -fsanitize=address
fsanitize: re

debug: CFLAGS += -g
debug: LIBFLAG += debug
debug: re

gdb: debug
	gdb -tui ./$(NAME)

valgrind: debug
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re debug gdb valgrind
