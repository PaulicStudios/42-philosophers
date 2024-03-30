/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:14:10 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/30 19:29:01 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_philo *first_philo)
{
	t_philo	*philo;
	t_philo	*next;

	pthread_mutex_destroy(&first_philo->info->m_log);
	pthread_mutex_destroy(&first_philo->info->m_stop);
	free(first_philo->info);
	philo = first_philo;
	while (philo)
	{
		pthread_mutex_destroy(&philo->m_fork);
		pthread_mutex_destroy(&philo->m_philo);
		next = philo->next;
		free(philo);
		philo = next;
		if (philo == first_philo)
			break ;
	}
}

void	ft_error(char *msg, t_philo *first_philo)
{
	ft_free(first_philo);
	printf("Error: %s\n", msg);
	exit(1);
}

bool	ft_check_finished(t_philo *first_philo)
{
	t_philo	*philo;

	philo = first_philo;
	while (philo)
	{
		pthread_mutex_lock(&philo->m_philo);
		if (philo->nbr_meals != -1
			&& philo->nbr_meals < philo->info->needed_meals)
		{
			pthread_mutex_unlock(&philo->m_philo);
			return (false);
		}
		pthread_mutex_unlock(&philo->m_philo);
		philo = philo->next;
		if (philo == first_philo)
			break ;
	}
	return (true);
}

void	ft_join_threads(t_philo *first_philo)
{
	t_philo	*philo;

	philo = first_philo;
	while (philo)
	{
		pthread_join(philo->thread_id, NULL);
		philo = philo->next;
		if (philo == first_philo)
			break ;
	}
	pthread_join(first_philo->info->waiter_id, NULL);
}

int	main(int argc, char **argv)
{
	t_info	*info;

	info = ft_parse_args(argc, argv);
	ft_start_routines(info);
	while (!ft_check_stop(info) && !ft_check_finished(info->first_philo))
	{
		usleep(100);
	}
	ft_join_threads(info->first_philo);
	ft_free(info->first_philo);
	return (0);
}
