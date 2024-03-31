/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 19:20:28 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/31 18:05:35 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_init_philo_sem_meals(t_philo *philo)
{
	char	*sem_name;

	sem_name = ft_philo_sem_meals_name(philo->id);
	sem_unlink(sem_name);
	philo->sem_meals = sem_open(sem_name, O_CREAT, 0644, 2);
	free(sem_name);
	if (philo->sem_meals == SEM_FAILED)
		ft_error_exit("sem_open failed", philo->info->first_philo);
}

t_philo	*ft_default_philo(t_philo *philo, t_philo **prev,
							unsigned int millis, unsigned int id)
{
	if (*prev)
		(*prev)->next = philo;
	philo->id = id;
	ft_init_philo_sem_meals(philo);
	philo->time_last_meal = millis;
	philo->nbr_meals = 0;
	philo->finished_meals = false;
	philo->prev = *prev;
	return (philo);
}

t_philo	*ft_create_philos(unsigned int nb_philo, t_info *info)
{
	t_philo			*first;
	t_philo			*prev;
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
			return (ft_error("malloc failed", first), NULL);
		philo->info = info;
		ft_default_philo(philo, &prev, millis, id);
		prev = philo;
	}
	philo->next = first;
	first->prev = philo;
	return (first);
}
