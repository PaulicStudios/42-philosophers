/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:42:41 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/30 23:08:49 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_kill_all(t_philo *philo)
{
	while (philo)
	{
		kill(philo->process_id, SIGKILL);
		philo = philo->next;
		if (philo == philo->info->first_philo)
			break ;
	}
}

void	*ft_monitor(void *philo_void)
{
	t_philo	*philo;
	int		status;

	philo = (t_philo *)philo_void;
	waitpid(philo->process_id, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == EXIT_FAILURE)
			ft_kill_all(philo->info->first_philo);
	}
	return (NULL);
}

void ft_start_monitor_threads(t_philo *philo)
{
	while (philo)
	{
		if (pthread_create(&philo->monitor_thread, NULL, ft_monitor, philo) != 0)
			ft_error_exit("pthread_create failed", philo);
		philo = philo->next;
		if (philo == philo->info->first_philo)
			break ;
	}
}
