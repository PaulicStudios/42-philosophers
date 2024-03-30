/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:12:30 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/30 19:32:57 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_wait_and_die(unsigned int time, t_philo *philo)
{
	unsigned int	die_time;

	die_time = philo->time_last_meal + philo->info->time_to_die;
	if (die_time < time)
	{
		ft_wait_until(die_time);
		ft_die(philo);
		return (true);
	}
	ft_wait_until(time);
	return (false);
}

void	*ft_philo_loop(void *philo_void)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *) philo_void;
	info = philo->info;
	while (!ft_check_stop(info) && !ft_check_dead(philo))
	{
		ft_log_is_thinking(philo);
		while (!ft_take_forks(philo))
		{
			if (ft_check_dead(philo))
				return (NULL);
			usleep(100);
		}
		if (!ft_eat(philo, info))
			return (NULL);
		if (!ft_sleep(philo, info))
			return (NULL);
	}
	return (NULL);
}

void	ft_start_routines(t_info *info)
{
	t_philo			*philo;

	ft_start_waiter(info);
	info->time_start = ft_get_millis();
	philo = info->first_philo;
	while (philo)
	{
		if (pthread_create(&philo->thread_id, NULL, ft_philo_loop, philo) != 0)
		{
			ft_error("Faield to create thread", info->first_philo);
		}
		philo = philo->next;
		if (philo == info->first_philo)
			break ;
	}
}
