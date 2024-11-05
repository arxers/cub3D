/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:44:00 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/05 21:03:34 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D_bonus.h"
#include "../inc/validate_input_bonus.h"

int	validate_input(int ac, char **av, t_scene *scene)
{
	if (check_n_cmdline_args(ac) == -1)
		return (-1);
	if (is_map_a_directory(av[1]) == -1)
		return (-1);
	if (is_map_a_dot_cub_file(av[1]) == -1)
		return (-1);
	if (is_map_file_openable(av[1]) == -1)
		return (-1);
	if (load_scene(av[1], scene) == -1)
		return (-1);
	return (0);
}

int	main_loop(t_game *game)
{
	if (game->state[S_MOUSE] && !game->state[S_PAUSE] && !game->state[S_CAUGHT])
		handle_mouselook(game);
	if (should_render_frame(game))
	{
		display_pause_screen(game);
		update_enemy_pos(game);
		handle_movement(game);
		render_walls(game);
		render_enemy_sprite(game);
		pickup_item(game);
		render_item(game);
		render_pwl(game);
		draw_minimap(game);
		mlx_put_image_to_window(game->mlx, game->win, game->img[T_WIN].img, 0,
			0);
		interact(game);
		display_fps_counter(game);
		display_msg(game);
	}
	return (0);
}

int	main(int ac, char **av)
{
	int		status;
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (validate_input(ac, av, &game.scene) == -1)
	{
		free_scene_struct(&game.scene);
		return (1);
	}
	status = init_game(&game, game.scene);
	free_scene_struct(&game.scene);
	if (status)
		error_handler(&game, status);
	mlx_do_key_autorepeatoff(game.mlx);
	mlx_hook(game.win, KeyPress, KeyPressMask, &key_press, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, &key_release, &game);
	mlx_hook(game.win, ButtonPress, ButtonPressMask, &mouse_event, &game);
	mlx_hook(game.win, DestroyNotify, DestroyAll, &exit_game, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
