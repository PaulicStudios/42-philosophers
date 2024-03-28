/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:14:07 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/28 17:54:18 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef enum e_philo_state
{
	STATE_EATING,
	STATE_SLEEPING,
	STATE_THINKING,
	STATE_DEAD
}	t_philo_state;

typedef struct s_philo t_philo;
struct s_philo
{
	unsigned int	id;
	t_philo_state	state;
	unsigned int	time_last_meal;
	unsigned int	nbr_meals;
	t_philo			*next;
	t_philo			*prev;
};

typedef struct s_info
{
	unsigned int	nb_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	needed_meals;
	t_philo			*first_philo;
}	t_info;


//main.c
void			ft_error(char *msg, t_philo *first_philo);

//parse.c
t_info			ft_parse_args(int argc, char **argv);

//utils.c
int				ft_atoi(const char *str);

//time_utils.c
unsigned int	ft_get_millis(void);

#endif
