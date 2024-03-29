/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:08:27 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/29 19:20:54 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_check_stop(t_info *info)
{
	bool	stop;

	pthread_mutex_lock(&info->m_stop);
	stop = info->stop;
	pthread_mutex_unlock(&info->m_stop);
	return (stop);
}

bool	ft_check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_philo);
	if (ft_get_millis() >= philo->time_last_meal + philo->info->time_to_die)
	{
		pthread_mutex_unlock(&philo->m_philo);
		ft_die(philo);
		return (true);
	}
	pthread_mutex_unlock(&philo->m_philo);
	return (false);
}
