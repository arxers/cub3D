/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaslim <jaslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:12:10 by jaslim            #+#    #+#             */
/*   Updated: 2024/11/04 23:28:52 by jaslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	delay_ms(unsigned int ms, struct timeval *timer)
{
	struct timeval	current_time;
	long			ms_elapsed;

	if (timer->tv_sec == 0 && timer->tv_usec == 0)
	{
		gettimeofday(timer, NULL);
		return (0);
	}
	gettimeofday(&current_time, NULL);
	ms_elapsed = (current_time.tv_sec - timer->tv_sec) * 1000;
	ms_elapsed += (current_time.tv_usec - timer->tv_usec) / 1000;
	if (ms_elapsed >= ms)
	{
		*timer = current_time;
		return (1);
	}
	return (0);
}

int	should_render_frame(t_game *game)
{
	long	elapsed;

	gettimeofday(&game->frame.current, NULL);
	elapsed = (game->frame.current.tv_sec - game->frame.last.tv_sec) * 1000
		+ (game->frame.current.tv_usec - game->frame.last.tv_usec) * 0.001;
	if (elapsed >= game->frame.time)
	{
		game->frame.fps++;
		game->frame.last = game->frame.current;
		if (delay_ms(1000, &game->timer[MS1000]))
		{
			ft_free(&game->frame.fps_str);
			game->frame.fps_str = ft_itoa(game->frame.fps);
			game->frame.fps = 0;
		}
		return (1);
	}
	return (0);
}
