/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:59:42 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/31 22:03:38 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_init_info(t_info *info)
{
	info->first_philo = ft_create_philos(info->nb_philo, info);
	info->stop = false;
	if (pthread_mutex_init(&info->m_log, NULL) != 0)
		return (ft_error("mutex init failed", info->first_philo));
	if (pthread_mutex_init(&info->m_stop, NULL) != 0)
		return (ft_error("mutex init failed", info->first_philo));
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

bool	ft_parse_argv_meals(int argc, char **argv, t_info *info)
{
	int	nbr;

	if (argc == 6)
	{
		nbr = ft_input_nbr(argv[5], info);
		if (nbr == -1)
			return (false);
		info->needed_meals = ft_input_nbr(argv[5], info);
	}
	else
		info->needed_meals = -1;
	return (true);
}

bool	ft_parse_argv(int argc, char **argv, t_info *info)
{
	int	nbr;

	nbr = ft_input_nbr(argv[1], info);
	if (nbr == -1)
		return (false);
	info->nb_philo = nbr;
	nbr = ft_input_nbr(argv[2], info);
	if (nbr == -1)
		return (false);
	info->time_to_die = nbr;
	nbr = ft_input_nbr(argv[3], info);
	if (nbr == -1)
		return (false);
	info->time_to_eat = nbr;
	nbr = ft_input_nbr(argv[4], info);
	if (nbr == -1)
		return (false);
	info->time_to_sleep = nbr;
	return (ft_parse_argv_meals(argc, argv, info));
}

t_info	*ft_parse_args(int argc, char **argv)
{
	t_info	*info;

	if (!ft_check_argc(argc))
		return (NULL);
	info = malloc(sizeof(t_info));
	if (!info)
		return (ft_error("malloc failed", NULL), NULL);
	if (!ft_parse_argv(argc, argv, info))
		return (NULL);
	if (!ft_init_info(info))
		return (NULL);
	return (info);
}
