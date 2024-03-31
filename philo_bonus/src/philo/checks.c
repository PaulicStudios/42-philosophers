/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:08:27 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/31 16:09:52 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	ft_check_dead(t_philo *philo)
{
	if (ft_get_millis() >= philo->time_last_meal + philo->info->time_to_die)
	{
		ft_die(philo);
		return (true);
	}
	return (false);
}
