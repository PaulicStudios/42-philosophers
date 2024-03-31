/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:42:41 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/31 16:53:34 by pgrossma         ###   ########.fr       */
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

bool	ft_all_finished(t_philo *philo)
{
	while (philo)
	{
		if (!philo->finished_meals)
			return (false);
		philo = philo->next;
		if (philo == philo->info->first_philo)
			break ;
	}
	return (true);
}

void	*ft_monitor_meals(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	usleep(200);
	sem_wait(philo->sem_meals);
	sem_wait(philo->info->sem_stop);
	philo->finished_meals = true;
	if (ft_all_finished(philo->info->first_philo) && !philo->info->stop)
	{
		ft_kill_all(philo->info->first_philo);
		philo->info->stop = true;
	}
	sem_post(philo->info->sem_stop);
	return (NULL);
}

void	*ft_monitor_alive(void *philo_void)
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
		if (pthread_create(&philo->monitor_alive_thread, NULL, ft_monitor_alive, philo) != 0)
			ft_error_exit("pthread_create failed", philo);
		if (pthread_create(&philo->monitor_meals_thread, NULL, ft_monitor_meals, philo) != 0)
			ft_error_exit("pthread_create failed", philo);
		philo = philo->next;
		if (philo == philo->info->first_philo)
			break ;
	}
}
