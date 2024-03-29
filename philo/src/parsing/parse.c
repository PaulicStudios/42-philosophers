/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:59:42 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/29 16:13:01 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_default_philo(t_philo *philo, t_info *info, unsigned int millis)
{
	philo->state = STATE_THINKING;
	philo->time_last_meal = millis;
	philo->nbr_meals = 0;
	philo->info = info;
	philo->fork_taken = false;
	if (pthread_mutex_init(&philo->m_fork, NULL) != 0)
		return ; //ToDo
}

t_philo	*ft_create_philos(unsigned int nb_philo, t_info *info)
{
	t_philo			*first;
	t_philo 		*prev;
	t_philo			*philo;
	unsigned int	id;
	unsigned int	millis;

	first = NULL;
	prev = NULL;
	millis = ft_get_millis();
	id = 0;
	while (id++ < nb_philo)
	{
		philo = malloc(sizeof(t_philo));
		if (!first)
			first = philo;
		if (!philo)
			ft_error("malloc failed", first);
		if (prev)
			prev->next = philo;
		philo->id = id;
		ft_default_philo(philo, info, millis);
		philo->prev = prev;
		prev = philo;
	}
	philo->next = first;
	first->prev = philo;
	return (first);
}

t_info	*ft_parse_args(int argc, char **argv)
{
	t_info	*info;

	if (argc < 5 || argc > 6)
	{
		write(2, "Error: wrong number of arguments\n", 34);
		write(2, "Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]\n", 95);
		exit(1);
	}
	info = malloc(sizeof(t_info));
	info->nb_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->needed_meals = ft_atoi(argv[5]);
	else
		info->needed_meals = -1;
	info->first_philo = ft_create_philos(info->nb_philo, info);
	info->stop = false;
	if (pthread_mutex_init(&info->m_log, NULL) != 0)
		ft_error("mutex init failed", info->first_philo);
	return (info);
}
