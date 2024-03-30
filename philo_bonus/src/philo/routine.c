/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:12:30 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/30 22:33:53 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	while (!ft_check_dead(philo))
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

bool	ft_start_routines(t_info *info)
{
	t_philo			*philo;

	info->time_start = ft_get_millis();
	philo = info->first_philo;
	while (philo)
	{
		philo->process_id = fork();
		if (philo->process_id == -1)
			return (ft_error("fork failed", info->first_philo));
		if (philo->process_id == 0)
		{
			ft_philo_loop(philo);
			exit(EXIT_SUCCESS);
		}
		philo = philo->next;
		if (philo == info->first_philo)
			break ;
	}
	return (true);
}
