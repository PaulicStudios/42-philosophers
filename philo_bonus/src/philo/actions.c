/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:12:39 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/30 22:27:32 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	ft_take_forks(t_philo *philo)
{
	if (philo->next == philo)
		return (false);
	sem_wait(philo->info->sem_forks);
	ft_log_taken_fork(philo);
	sem_wait(philo->info->sem_forks);
	ft_log_taken_fork(philo);
	return (true);
}

void	ft_drop_forks(t_philo *philo)
{
	sem_post(philo->info->sem_forks);
	sem_post(philo->info->sem_forks);
}

void	ft_die(t_philo *philo)
{
	ft_log_died(philo);
	ft_stop(philo->info);
}

bool	ft_eat(t_philo *philo, t_info *info)
{
	unsigned int	wait_time;

	ft_log_is_eating(philo);
	philo->time_start_eating = ft_get_millis();
	wait_time = philo->time_start_eating + info->time_to_eat;
	if (ft_wait_and_die(wait_time, philo))
	{
		ft_drop_forks(philo);
		return (false);
	}
	ft_drop_forks(philo);
	philo->nbr_meals++;
	if (info->needed_meals != -1 && philo->nbr_meals >= info->needed_meals)
		ft_stop(info);
	philo->time_last_meal = ft_get_millis();
	return (true);
}

bool	ft_sleep(t_philo *philo, t_info *info)
{
	unsigned int	wait_time;

	ft_log_is_sleeping(philo);
	wait_time = philo->time_last_meal + info->time_to_sleep;
	return (!ft_wait_and_die(wait_time, philo));
}
