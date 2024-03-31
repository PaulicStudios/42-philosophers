/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:14:07 by pgrossma          #+#    #+#             */
/*   Updated: 2024/03/30 21:15:49 by pgrossma         ###   ########.fr       */
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
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo	t_philo;
typedef struct s_info	t_info;

struct s_philo
{
	unsigned int	id;
	pid_t			process_id;
	pthread_t		monitor_alive_thread;
	pthread_t		monitor_meals_thread;
	unsigned int	time_start_eating;
	unsigned int	time_last_meal;
	int				nbr_meals;
	bool			finished_meals;
	sem_t			*sem_meals;
	t_philo			*next;
	t_philo			*prev;
	t_info			*info;
};

struct s_info
{
	bool			stop;
	unsigned int	time_start;
	unsigned int	nb_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				needed_meals;
	t_philo			*first_philo;
	sem_t			*sem_forks;
	sem_t			*sem_log;
	sem_t			*sem_stop;
};

//main.c
bool			ft_error(char *msg, t_philo *first_philo);
void			ft_error_exit(char *msg, t_philo *first_philo);
void			ft_free(t_philo *first_philo);

//routine.c
bool			ft_start_routines(t_info *info);
bool			ft_wait_and_die(unsigned int time, t_philo *philo);

//monitor.c
void			 ft_start_monitor_threads(t_philo *philo);

//actions.c
bool			ft_take_forks(t_philo *philo);
void			ft_drop_forks(t_philo *philo);
void			ft_die(t_philo *philo);
bool			ft_eat(t_philo *philo, t_info *info);
bool			ft_sleep(t_philo *philo, t_info *info);

//log.c
void			ft_print_log(const char *msg, t_philo *philo, bool die_log);

//log_wrapper.c
void			ft_log_taken_fork(t_philo *philo);
void			ft_log_is_eating(t_philo *philo);
void			ft_log_is_sleeping(t_philo *philo);
void			ft_log_is_thinking(t_philo *philo);
void			ft_log_died(t_philo *philo);

//checks.c
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
void			ft_stop(t_philo *philo, int exit_status);

//ft_itoa.c
char			*ft_itoa(int n);
char			*ft_strjoin(char const *s1, char const *s2);

#endif
