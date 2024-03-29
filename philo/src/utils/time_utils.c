/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:36:38 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/29 17:26:26 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_get_millis(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_wait_until(unsigned int time)
{
	unsigned int	diff_time;
	unsigned int	current_time;

	while (true)
	{
		current_time = ft_get_millis();
		if (current_time >= time)
			break ;
		diff_time = (time - current_time) * 1000;
		if (diff_time > 100)
			usleep(diff_time);
		else
			usleep(100);
	}
	// while (ft_get_millis() < time)
	// {
	// 	usleep(100);
	// }
}
