/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:14:10 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/28 19:54:26 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *msg, t_philo *first_philo)
{
	while (first_philo)
	{
		pthread_mutex_destroy(&first_philo->m_fork);
		free(first_philo);
		first_philo = first_philo->next;
	}
	printf("Error: %s\n", msg);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_info	info;

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
	ft_start_routines(&info);

	while (true);
	return (0);
}
