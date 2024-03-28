/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:55:23 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/28 19:06:58 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_print_log(const char *msg, t_philo *philo)
{
	printf("%u %u %s\n", ft_get_millis(), philo->id, msg);
}

void	ft_log_taken_fork(t_philo *philo)
{
	ft_print_log("has taken a fork", philo);
}

void	ft_log_is_eating(t_philo *philo)
{
	ft_print_log("is eating", philo);
}

void	ft_log_is_sleeping(t_philo *philo)
{
	ft_print_log("is sleeping", philo);
}

void	ft_log_is_thinking(t_philo *philo)
{
	ft_print_log("is thinking", philo);
}

void	ft_log_died(t_philo *philo)
{
	ft_print_log("died", philo);
}
