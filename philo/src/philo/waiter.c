/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:06:26 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/30 18:56:36 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_all_ate(t_philo *philo)
{
	while (philo)
	{
		pthread_mutex_lock(&philo->m_fork);
		if (philo->is_allowed_to_eat)
		{
			pthread_mutex_unlock(&philo->m_fork);
			return (false);
		}
		pthread_mutex_unlock(&philo->m_fork);
		philo = philo->next;
		if (philo == philo->info->first_philo)
			break ;
	}
	return (true);
}

void	*ft_waiter(void *info_void)
{
	t_info	*info;
	t_philo	*philo;

	info = (t_info *)info_void;
	philo = info->first_philo;
	while (philo)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&philo->m_fork);
			philo->is_allowed_to_eat = true;
			pthread_mutex_unlock(&philo->m_fork);
		}
		philo = philo->next;
		if (philo == info->first_philo)
			break ;
	}
	while (!ft_check_stop(info))
	{
		while (!ft_all_ate(philo))
		{
			if (ft_check_stop(info))
				return(NULL);
			usleep(100);
		}
		philo = info->first_philo;
		while (philo)
		{
			if (philo->ate)
			{
				pthread_mutex_lock(&philo->m_fork);
				pthread_mutex_lock(&philo->next->m_fork);
				philo->ate = false;
				philo->next->is_allowed_to_eat = true;
				pthread_mutex_unlock(&philo->m_fork);
				pthread_mutex_unlock(&philo->next->m_fork);
			}
			philo = philo->next;
			if (philo == info->first_philo)
				break ;
		}
	}
	return (NULL);
}

void	ft_start_waiter(t_info *info)
{
	if (pthread_create(&info->waiter_id, NULL, ft_waiter, info) != 0)
	{
		ft_error("Failed to create waiter thread", info->first_philo);
	}
}
