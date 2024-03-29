/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:14:10 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/29 15:15:35 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_philo *first_philo)
{
	free(first_philo->info);
	while (first_philo)
	{
		pthread_mutex_destroy(&first_philo->m_fork);
		first_philo = first_philo->next;
		free(first_philo);
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
		if (philo->state != STATE_FINISHED)
			return (false);
		philo = philo->next;
		if (philo == first_philo)
			break ;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_info	*info;

	info = ft_parse_args(argc, argv);
	// t_philo	*philo = info.first_philo;
	// while (philo)
	// {
	// 	printf("philo %d\n", philo->id);
	// 	printf("state: %d\n", philo->state);
	// 	printf("time_last_meal: %u\n", philo->time_last_meal);
	// 	printf("nbr_meals: %d\n", philo->nbr_meals);
	// 	philo = philo->next;
	// 	if (philo == info.first_philo)
	// 		break ;
	// }
	// printf("nb_philo: %u\n", info.nb_philo);
	// printf("time_to_die: %u\n", info.time_to_die);
	// printf("time_to_eat: %u\n", info.time_to_eat);
	// printf("time_to_sleep: %u\n", info.time_to_sleep);
	// printf("needed_meals: %d\n", info.needed_meals);

	ft_start_routines(info);

	while (!info->stop && !ft_check_finished(info->first_philo));
	// ft_free(info->first_philo);
	return (0);
}
