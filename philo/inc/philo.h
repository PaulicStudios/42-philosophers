/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:14:07 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/28 19:52:56 by pgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef enum e_philo_state
{
	STATE_EATING,
	STATE_SLEEPING,
	STATE_THINKING,
	STATE_FINISHED
}	t_philo_state;

typedef struct s_philo t_philo;
typedef struct s_info t_info;

struct s_philo
{
	unsigned int	id;
	pthread_t		thread_id;
	t_philo_state	state;
	unsigned int	time_start_eating;
	unsigned int	time_start_sleeping;
	unsigned int	time_last_meal;
	int				nbr_meals;
	bool			fork_taken;
	pthread_mutex_t	m_fork;
	t_philo			*next;
	t_philo			*prev;
	t_info			*info;
};

struct s_info
{
	bool			stop;
	unsigned int	nb_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				needed_meals;
	t_philo			*first_philo;
};


//main.c
void			ft_error(char *msg, t_philo *first_philo);

//routine.c
void			ft_start_routines(t_info *info);

//actions.c
bool			ft_take_forks(t_philo *philo);
void			ft_drop_forks(t_philo *philo);

//log.c
void			ft_log_taken_fork(t_philo *philo);
void			ft_log_is_eating(t_philo *philo);
void			ft_log_is_sleeping(t_philo *philo);
void			ft_log_is_thinking(t_philo *philo);
void			ft_log_died(t_philo *philo);

//parse.c
t_info			ft_parse_args(int argc, char **argv);

//utils.c
int				ft_atoi(const char *str);

//time_utils.c
unsigned int	ft_get_millis(void);

#endif
