/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:21:19 by abouclie          #+#    #+#             */
/*   Updated: 2025/06/03 12:41:00 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_args
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_times_must_eat;
}				t_args;

typedef struct s_philo
{
	int				number;
	int				is_eating;
	pthread_t		philosopher;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*error_mutex;
	t_args			*args;
	int				*someone_died;
	int				*error;
	long			last_meal_time;
}				t_philo;

typedef struct s_data
{
	t_args			args;
	t_philo			*philo;
	pthread_t		monitor;
	long			start_time;
	int				someone_died;
	int				error;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	error_mutex;
}				t_data;

int			check_arg(int argc, char **argv);
int			str_is_digit(char *str);
int			init_philosophers(t_data *data);
int			wait_for_threads(t_data *data);
long		current_time_ms(void);
long		ft_atoi(const char *nptr, int *error);
void		start_thread(t_data *data);
void		init_args(char **argv, t_args *args);
void		free_all(t_data *data);
void		*routine(void *arg);
void		*monitor_death(void *arg);
int		philo_eat(t_philo *philo);
int		philo_think(t_philo *philo);
int		philo_sleep(t_philo *philo);
int			safe_mutex_lock(pthread_mutex_t *mutex, int *error);
int			safe_mutex_unlock(pthread_mutex_t *mutex, int *error);

/* A supprimer */
void	print_args(t_args *args);

#endif