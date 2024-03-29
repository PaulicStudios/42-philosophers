/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:12:39 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/29 19:07:57 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_take_forks(t_philo *philo)
{
	if (philo->next == philo)
		return (false);
	pthread_mutex_lock(&philo->m_fork);
	pthread_mutex_lock(&philo->next->m_fork);
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
