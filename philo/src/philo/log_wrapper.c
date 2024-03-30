/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_wrapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 19:32:13 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/30 19:32:17 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
