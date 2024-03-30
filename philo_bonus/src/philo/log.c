/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:55:23 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/30 22:31:10 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print_log(const char *msg, t_philo *philo)
{
	sem_wait(philo->info->sem_log);
	printf("%u %u %s\n", (ft_get_millis() - philo->info->time_start),
		philo->id, msg);
	sem_post(philo->info->sem_log);
}
