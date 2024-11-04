NAME = cub3D
CFLAGS = -Wall -Wextra -Werror
SRC =   src/main.c \
		src/cleanup.c \
		src/init_game.c \
		src/init_game_utils.c \
		src/init_image.c \
		src/init_map.c \
		src/background.c \
		src/key_hooks.c \
		src/key_specials.c \
		src/mouse_event.c \
		src/image_utils.c \
		src/image_pixel_utils.c \
		src/image_primitives.c \
		src/image_copy_paste.c \
		src/minimap.c \
		src/player_movement.c \
		src/player_look.c \
		src/player_utils.c \
		src/display_ui.c \
		src/interact.c \
		src/raycasting.c src/dda.c src/dda_special.c \
		src/utils.c \
		src/validate_bonus_cub_file.c \
		src/load_scene_details.c \
		src/load_scene_details_to_struct.c \
		src/prepare_walls.c \
		src/is_valid_rgb_array.c \
		src/is_bonus_map_char_valid.c \
		src/process_map.c \
		src/is_bonus_map_valid.c \
		src/load_bonus_chars.c \
		src/is_fill_char_at_map_border.c \
		src/validate_input.c
		
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
