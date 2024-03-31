/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:14:10 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/31 17:54:49 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_wait_finish(t_info *info)
{
	while (true)
	{
		sem_wait(info->sem_stop);
		if (info->stop)
		{
			sem_post(info->sem_stop);
			break ;
		}
		sem_post(info->sem_stop);
		usleep(500);
	}
}

void	ft_detach_threads(t_philo *first_philo)
{
	t_philo	*philo;

	philo = first_philo;
	while (philo)
	{
		pthread_detach(philo->monitor_alive_thread);
		pthread_detach(philo->monitor_meals_thread);
		philo = philo->next;
		if (philo == first_philo)
			break ;
	}
}

int	main(int argc, char **argv)
{
	t_info	*info;

	info = ft_parse_args(argc, argv);
	if (!info)
		return (1);
	if (!ft_start_routines(info))
		return (1);
	ft_wait_finish(info);
	ft_wait_until(ft_get_millis() + 1000);
	ft_detach_threads(info->first_philo);
	ft_free(info->first_philo);
	return (0);
}
