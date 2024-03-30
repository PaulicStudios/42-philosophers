/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:14:07 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/30 19:34:02 by pgrossma         ###   ########.fr       */
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

typedef struct s_philo	t_philo;
typedef struct s_info	t_info;

struct s_philo
{
	unsigned int	id;
	pthread_t		thread_id;
	unsigned int	time_start_eating;
	unsigned int	time_last_meal;
	int				nbr_meals;
	bool			is_allowed_to_eat;
	bool			ate;
	pthread_mutex_t	m_fork;
	pthread_mutex_t	m_philo;
	t_philo			*next;
	t_philo			*prev;
	t_info			*info;
};

struct s_info
{
	bool			stop;
	pthread_mutex_t	m_stop;
	unsigned int	time_start;
	unsigned int	nb_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				needed_meals;
	t_philo			*first_philo;
	pthread_mutex_t	m_log;
	pthread_t		waiter_id;
};

//main.c
void			ft_error(char *msg, t_philo *first_philo);

//routine.c
void			ft_start_routines(t_info *info);
bool			ft_wait_and_die(unsigned int time, t_philo *philo);

//waiter.c
void			ft_start_waiter(t_info *info);

//actions.c
bool			ft_take_forks(t_philo *philo);
void			ft_drop_forks(t_philo *philo);
void			ft_die(t_philo *philo);
bool			ft_eat(t_philo *philo, t_info *info);
bool			ft_sleep(t_philo *philo, t_info *info);

//log.c
void			ft_print_log(const char *msg, t_philo *philo);

//log_wrapper.c
void			ft_log_taken_fork(t_philo *philo);
void			ft_log_is_eating(t_philo *philo);
void			ft_log_is_sleeping(t_philo *philo);
void			ft_log_is_thinking(t_philo *philo);
void			ft_log_died(t_philo *philo);

//checks.c
bool			ft_check_stop(t_info *info);
bool			ft_check_dead(t_philo *philo);

//parse.c
t_info			*ft_parse_args(int argc, char **argv);

//create_philos.c
t_philo			*ft_create_philos(unsigned int nb_philo, t_info *info);

//utils.c
unsigned int	ft_input_nbr(const char *str, t_info *info);

//time_utils.c
unsigned int	ft_get_millis(void);
void			ft_wait_until(unsigned int time);

//action_utils.c
void			ft_stop(t_info *info);

#endif
