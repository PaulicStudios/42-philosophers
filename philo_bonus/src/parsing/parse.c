/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:59:42 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/31 16:07:19 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	ft_init_info(t_info *info)
{
	info->first_philo = ft_create_philos(info->nb_philo, info);
	info->stop = false;
	sem_unlink("sem_forks");
	sem_unlink("sem_log");
	sem_unlink("sem_stop");
	info->sem_forks = sem_open("sem_forks", O_CREAT, 0644, info->nb_philo);
	if (info->sem_forks == SEM_FAILED)
		return (ft_error("sem_open failed", info->first_philo), false);
	info->sem_log = sem_open("sem_log", O_CREAT, 0644, 1);
	if (info->sem_log == SEM_FAILED)
		return (ft_error("sem_open failed", info->first_philo), false);
	info->sem_stop = sem_open("sem_stop", O_CREAT, 0644, 1);
	if (info->sem_stop == SEM_FAILED)
		return (ft_error("sem_open failed", info->first_philo), false);
	return (true);
}

bool	ft_check_argc(int argc)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Error: wrong number of arguments\n", 34);
		write(2, "Usage: ./philo number_of_philosophers time_to_die "
			"time_to_eat time_to_sleep [number_of_meals]\n", 95);
		return (false);
	}
	return (true);
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

	if (!ft_check_argc(argc))
		return (NULL);
	info = malloc(sizeof(t_info));
	if (!info)
		return (ft_error("malloc failed", NULL), NULL);
	ft_parse_argv(argc, argv, info);
	if (!ft_init_info(info))
		return (NULL);
	return (info);
}
