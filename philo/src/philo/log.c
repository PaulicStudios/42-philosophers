/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:55:23 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/30 19:32:02 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_log(const char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->m_log);
	pthread_mutex_lock(&philo->info->m_stop);
	if (philo->info->stop)
	{
		pthread_mutex_unlock(&philo->info->m_stop);
		pthread_mutex_unlock(&philo->info->m_log);
		return ;
	}
	printf("%u %u %s\n", (ft_get_millis() - philo->info->time_start),
		philo->id, msg);
	pthread_mutex_unlock(&philo->info->m_log);
	pthread_mutex_unlock(&philo->info->m_stop);
}
