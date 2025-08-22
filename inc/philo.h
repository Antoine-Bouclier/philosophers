/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 08:41:46 by abouclie          #+#    #+#             */
/*   Updated: 2025/08/22 08:56:41 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define Philo_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define RED    "\033[31m"
#define YELLOW "\033[33m"
#define RESET  "\033[0m"

#define STR_ARG "./philo " RED "<nb_of_philo> <time_to_die> <time_to_eat> <time_to_sleep> " RESET \
YELLOW "optional: <number_of_times_each_philo_must_eat>" RESET

# define STR_MTX_LOCK "Error! mutex lock failed."

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
}				t_philo;

typedef struct s_table
{
	int				nb_philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	long			start_time;
	int				simulation_over;
	pthread_mutex_t	simulation_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	pthread_t		monitor;
	t_philo			*philos;
}				t_table;

int		check_arg(int argc, char **argv);

int		error_msg(char *str, int ret);
void	*error_null(char *str);
void	free_all(t_table *table);

long	current_time_ms(void);
long	ft_atoi(const char *nptr, int *error);

t_table	*init(char **argv);

void	*routine(void *arg);
void	*monitor_death(void *arg);
int		has_stopped(t_table *table);

void	destroy_mutex_forks(pthread_mutex_t	*forks, int last_index);
void	destroy_mutex(t_table *table);

int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		philo_think(t_philo *philo);

void	wait_until(long target_time);

void	*routine_alone(void *arg);
int		start_one_thread(t_table *table);

/* A supprimer */
void	print_argv(t_table *table);

# endif