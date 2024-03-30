/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:59:42 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/30 19:30:05 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_info(t_info *info)
{
	info->first_philo = ft_create_philos(info->nb_philo, info);
	info->stop = false;
	if (pthread_mutex_init(&info->m_log, NULL) != 0)
		ft_error("mutex init failed", info->first_philo);
	if (pthread_mutex_init(&info->m_stop, NULL) != 0)
		ft_error("mutex init failed", info->first_philo);
}

void	ft_check_argc(int argc)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Error: wrong number of arguments\n", 34);
		write(2, "Usage: ./philo number_of_philosophers time_to_die time_to_eat \
				time_to_sleep [number_of_meals]\n", 95);
		exit(EXIT_FAILURE);
	}
}

void	ft_parse_argv(int argc, char **argv, t_info *info)
{
	info->nb_philo = ft_input_nbr(argv[1], info);
	info->time_to_die = ft_input_nbr(argv[2], info);
	info->time_to_eat = ft_input_nbr(argv[3], info);
	info->time_to_sleep = ft_input_nbr(argv[4], info);
	if (argc == 6)
		info->needed_meals = ft_input_nbr(argv[5], info);
	else
		info->needed_meals = -1;
}

t_info	*ft_parse_args(int argc, char **argv)
{
	t_info	*info;

	ft_check_argc(argc);
	info = malloc(sizeof(t_info));
	ft_parse_argv(argc, argv, info);
	ft_init_info(info);
	return (info);
}
