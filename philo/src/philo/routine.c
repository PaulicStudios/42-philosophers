/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:12:30 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/29 16:52:16 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_check_dead(t_philo *philo)
{
	if (ft_get_millis() >= philo->time_last_meal + philo->info->time_to_die)
	{
		ft_die(philo);
		return (true);
	}
	return (false);
}

bool	ft_wait_or_die(unsigned int millis, t_philo *philo)
{
	unsigned int	die_time;
	unsigned int	wait_time;
	unsigned int	current_time;

	current_time = ft_get_millis();
	die_time = philo->time_last_meal + philo->info->time_to_die;
	wait_time = current_time + millis;
	if (die_time < wait_time)
	{
		ft_wait_millis(die_time - current_time);
		ft_die(philo);
	}
	ft_wait_millis(millis);
	return (true);
}

void	*ft_philo_loop(void *philo_void)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *) philo_void;
	info = philo->info;
	while (!info->stop && philo->state != STATE_FINISHED)
	{
		if (ft_check_dead(philo))
			return (NULL);
		if (philo->state == STATE_THINKING)
		{
			// ft_wait_millis(1);
			if (!ft_take_forks(philo))
				continue;
			ft_log_taken_fork(philo);
			philo->state = STATE_EATING;
			philo->time_start_eating = ft_get_millis();
			ft_log_is_eating(philo);
			ft_wait_or_die(info->time_to_eat, philo);
		}
		else if (philo->state == STATE_EATING)
		{
			if (ft_get_millis() < philo->time_start_eating + info->time_to_eat)
				continue;
			ft_drop_forks(philo);
			philo->nbr_meals++;
			if (info->needed_meals != -1 && philo->nbr_meals == info->needed_meals)
			{
				philo->state = STATE_FINISHED;
				return (NULL);
			}
			philo->state = STATE_SLEEPING;
			philo->time_last_meal = ft_get_millis();
			ft_log_is_sleeping(philo);
			ft_wait_or_die(info->time_to_sleep, philo);
		}
		else if (philo->state == STATE_SLEEPING)
		{
			if (ft_get_millis() < philo->time_last_meal + info->time_to_sleep)
				continue;
			philo->state = STATE_THINKING;
			ft_log_is_thinking(philo);
		}
	}
	return (NULL);
}

void	ft_start_routines(t_info *info)
{
	t_philo			*philo;

	info->time_start = ft_get_millis();
	philo = info->first_philo;
	while (philo)
	{
		if (pthread_create(&philo->thread_id, NULL, ft_philo_loop, philo) != 0)
		{
			ft_error("Faield to create thread", info->first_philo);
		}
		philo = philo->next;
		if (philo == info->first_philo)
			break;
	}
}
