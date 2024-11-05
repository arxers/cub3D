NAME = cub3D
BNAME = cub3D_bonus
CFLAGS = -Wall -Wextra -Werror
SRC =   src/main.c src/cleanup.c src/timers.c \
		src/init_game.c src/init_game_utils.c src/init_image.c src/init_map.c \
		src/key_hooks.c src/key_specials.c src/mouse_event.c \
		src/image_utils.c src/image_pixel_utils.c src/image_primitives.c \
		src/minimap.c src/display_ui.c \
		src/player_movement.c src/player_look.c src/player_utils.c \
		src/raycasting.c src/dda.c src/background.c \
		src/validate_input.c src/validate_cub_file.c \
		src/load_scene_details.c src/load_scene_details_to_struct.c \
		src/prepare_walls.c src/process_map.c \
		src/is_valid_rgb_array.c src/is_map_char_valid.c src/is_map_valid.c \
		src/is_fill_char_at_map_border.c

BSRC =	src_bonus/main_bonus.c src_bonus/cleanup_bonus.c \
		src_bonus/init_game_bonus.c src_bonus/init_game_utils_bonus.c \
		src_bonus/init_image_bonus.c src_bonus/init_map_bonus.c \
		src_bonus/background_bonus.c \
		src_bonus/key_hooks_bonus.c src_bonus/key_specials_bonus.c \
		src_bonus/mouse_event_bonus.c \
		src_bonus/image_utils_bonus.c src_bonus/image_pixel_utils_bonus.c \
		src_bonus/image_primitives_bonus.c src_bonus/image_copy_paste_bonus.c \
		src_bonus/minimap_bonus.c src_bonus/enemy_hunt_bonus.c \
		src_bonus/enemy_chase_bonus.c src_bonus/enemy_render_bonus.c \
		src_bonus/player_movement_bonus.c src_bonus/player_look_bonus.c \
		src_bonus/player_utils_bonus.c src_bonus/display_ui_bonus.c \
		src_bonus/interact_bonus.c src_bonus/raycasting_bonus.c \
		src_bonus/dda_bonus.c src_bonus/dda_special_bonus.c \
		src_bonus/pwl_render_bonus.c src_bonus/item_bonus.c \
		src_bonus/utils_bonus.c src_bonus/validate_cub_file_bonus.c \
		src_bonus/load_scene_details_bonus.c \
		src_bonus/load_scene_details_to_struct_bonus.c \
		src_bonus/prepare_walls_bonus.c src_bonus/is_valid_rgb_array_bonus.c \
		src_bonus/is_map_char_valid_bonus.c src_bonus/is_map_valid_bonus.c \
		src_bonus/is_fill_char_at_map_border_bonus.c src_bonus/process_map_bonus.c \
		src_bonus/load_chars_bonus.c

OBJ = $(SRC:.c=.o)
BOBJ = $(BSRC:.c=.o)

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

$(LIBFT): 
	make $(LIBFLAG) -C libft

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	cc $(CFLAGS) $(OBJ) $(LIBRARY) $(LIBRARY_FLAGS) -o $(NAME)

bonus: $(MLX) $(LIBFT) $(BOBJ)
	cc $(CFLAGS) $(BOBJ) $(LIBRARY) $(LIBRARY_FLAGS) -o $(BNAME)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BOBJ)
	make -C libft clean
	make -C $(MLXDIR) clean

fclean: clean
	rm -f $(NAME) $(BNAME)
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

.PHONY: all bonus clean fclean re debug gdb valgrind
