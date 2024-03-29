/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:12:39 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/29 20:35:15 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_take_forks(t_philo *philo)
{
	if (philo->next == philo)
		return (false);
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->m_fork);
		pthread_mutex_lock(&philo->next->m_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->next->m_fork);
		pthread_mutex_lock(&philo->m_fork);
	}
	ft_log_taken_fork(philo);
	return (true);
}

void	ft_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->m_fork);
	pthread_mutex_unlock(&philo->next->m_fork);
}

void	ft_die(t_philo *philo)
{
	ft_log_died(philo);
	pthread_mutex_lock(&philo->info->m_stop);
	philo->info->stop = true;
	pthread_mutex_unlock(&philo->info->m_stop);
}

bool	ft_eat(t_philo *philo, t_info *info)
{
	unsigned int	wait_time;

	ft_log_is_eating(philo);
	pthread_mutex_lock(&philo->m_philo);
	philo->time_start_eating = ft_get_millis();
	wait_time = philo->time_start_eating + info->time_to_eat;
	pthread_mutex_unlock(&philo->m_philo);
	if (ft_die_while_wait(wait_time, philo))
	{
		ft_drop_forks(philo);
		return (false);
	}
	ft_drop_forks(philo);
	pthread_mutex_lock(&philo->m_philo);
	philo->nbr_meals++;
	if (info->needed_meals != -1 && philo->nbr_meals == info->needed_meals)
	{
		pthread_mutex_unlock(&philo->m_philo);
		return (false);
	}
	philo->time_last_meal = ft_get_millis();
	pthread_mutex_unlock(&philo->m_philo);
	return (true);
}

bool	ft_sleep(t_philo *philo, t_info *info)
{
	unsigned int	wait_time;

	ft_log_is_sleeping(philo);
	pthread_mutex_lock(&philo->m_philo);
	wait_time = philo->time_last_meal + info->time_to_sleep;
	pthread_mutex_unlock(&philo->m_philo);
	return (!ft_die_while_wait(wait_time, philo));
}
