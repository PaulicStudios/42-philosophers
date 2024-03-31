/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:38:03 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/31 17:41:23 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_close_sems(t_info *info)
{
	sem_unlink("sem_forks");
	sem_unlink("sem_log");
	sem_unlink("sem_stop");
	sem_close(info->sem_forks);
	sem_close(info->sem_log);
	sem_close(info->sem_stop);
}

void	ft_free(t_philo *first_philo)
{
	t_philo	*philo;
	t_philo	*next;
	t_info	*info;
	char	*sem_meals_name;

	info = first_philo->info;
	philo = first_philo;
	while (philo)
	{
		next = philo->next;
		sem_meals_name = ft_philo_sem_meals_name(philo->id);
		sem_unlink(sem_meals_name);
		free(sem_meals_name);
		sem_close(philo->sem_meals);
		free(philo);
		philo = next;
		if (philo == first_philo)
			break ;
	}
	ft_close_sems(info);
	free(info);
}

bool	ft_error(char *msg, t_philo *first_philo)
{
	ft_free(first_philo);
	printf("Error: %s\n", msg);
	return (false);
}

void	ft_error_exit(char *msg, t_philo *first_philo)
{
	ft_free(first_philo);
	printf("Error: %s\n", msg);
	exit(EXIT_FAILURE);
}
