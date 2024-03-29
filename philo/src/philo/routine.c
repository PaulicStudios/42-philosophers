/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:12:30 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/29 18:23:51 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_check_dead(t_philo *philo)
{
	if (ft_get_millis() >= philo->time_last_meal + philo->info->time_to_die)
	{
		ft_die(philo);
		return (true);
	}
	return (false);
}

bool	ft_wait_or_die(unsigned int time, t_philo *philo)
{
	unsigned int	die_time;

	die_time = philo->time_last_meal + philo->info->time_to_die;
	if (die_time < time)
	{
		ft_wait_until(die_time);
		ft_die(philo);
		return (false);
	}
	ft_wait_until(time);
	return (true);
}

void	*ft_philo_loop(void *philo_void)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *) philo_void;
	info = philo->info;
	while (!info->stop)
	{
		while (!ft_take_forks(philo))
		{
			if (ft_check_dead(philo))
				return (NULL);
			usleep(100);
		}
		ft_log_taken_fork(philo);
		philo->time_start_eating = ft_get_millis();
		ft_log_is_eating(philo);
		if (!ft_wait_or_die(philo->time_start_eating + info->time_to_eat, philo))
		{
			ft_drop_forks(philo);
			return (NULL);
		}
		ft_drop_forks(philo);
		philo->nbr_meals++;
		if (info->needed_meals != -1 && philo->nbr_meals == info->needed_meals)
			return (NULL);
		philo->time_last_meal = ft_get_millis();
		ft_log_is_sleeping(philo);
		if (!ft_wait_or_die(philo->time_last_meal + info->time_to_sleep, philo))
			return (NULL);
		ft_log_is_thinking(philo);
	}
	return (NULL);
}

void	ft_start_routines(t_info *info)
{
	t_philo			*philo;

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
			break;
	}
}
