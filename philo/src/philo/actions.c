/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:12:39 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/29 15:51:04 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_take_forks(t_philo *philo)
{
	if (philo->next == philo)
		return (false);
	if (philo->fork_taken || philo->next->fork_taken)
		return (false);
	pthread_mutex_lock(&philo->m_fork);
	pthread_mutex_lock(&philo->next->m_fork);
	philo->fork_taken = true;
	philo->next->fork_taken = true;
	pthread_mutex_unlock(&philo->m_fork);
	pthread_mutex_unlock(&philo->next->m_fork);
	return (true);
}

void	ft_drop_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_fork);
	pthread_mutex_lock(&philo->next->m_fork);
	philo->fork_taken = false;
	philo->next->fork_taken = false;
	pthread_mutex_unlock(&philo->m_fork);
	pthread_mutex_unlock(&philo->next->m_fork);
}
