/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:14:10 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/30 22:33:45 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_free(t_philo *first_philo)
{
	t_philo	*philo;
	t_philo	*next;

	free(first_philo->info);
	philo = first_philo;
	while (philo)
	{
		next = philo->next;
		free(philo);
		philo = next;
		if (philo == first_philo)
			break ;
	}
	sem_close(first_philo->info->sem_forks);
	sem_close(first_philo->info->sem_log);
	sem_unlink("sem_forks");
	sem_unlink("sem_log");
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

bool	ft_check_finished(t_philo *philo)
{
	if (philo->info->needed_meals == -1)
		return (false);
	while (philo)
	{
		philo = philo->next;
		if (philo == philo->info->first_philo)
			break ;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_info	*info;

	info = ft_parse_args(argc, argv);
	if (!info)
		return (1);
	if (!ft_start_routines(info))
		return (1);
	while (!ft_check_finished(info->first_philo))
	{
		usleep(100);
	}
	ft_free(info->first_philo);
	return (0);
}
