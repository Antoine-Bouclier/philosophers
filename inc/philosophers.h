/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:21:19 by abouclie          #+#    #+#             */
/*   Updated: 2025/05/29 11:52:52 by abouclie         ###   ########.fr       */
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
	t_args			*args;
	int				*someone_died;
	long			last_meal_time;
}				t_philo;

typedef struct s_data
{
	t_args			args;
	t_philo			*philo;
	long			start_time;
	int				someone_died;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
}				t_data;

int			check_arg(int argc, char **argv);
int			str_is_digit(char *str);
int			init_philosophers(t_data *data);
int			start_thread(t_data *data);
int			wait_for_threads(t_data *data);
long		current_time_ms(void);
long		ft_atoi(const char *nptr, int *error);
void		init_args(char **argv, t_args *args);
void		free_all(t_data *data);
void		*routine(void *arg);
void		philo_eat(t_philo *philo);
void		philo_think(t_philo *philo);
void		philo_sleep(t_philo *philo);

/* A supprimer */
void	print_args(t_args *args);

#endif