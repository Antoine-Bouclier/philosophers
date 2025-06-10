/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 08:41:46 by abouclie          #+#    #+#             */
/*   Updated: 2025/06/10 14:53:34 by abouclie         ###   ########.fr       */
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

# define STR_ARG "./philo <nb_of_philo> <time_to_die> \
<time_to_eat> <time_to_sleep> \
optional: <number_of_times_each_philo_must_eat>"

# define STR_MTX_LOCK "Error! mutex lock failed."
# define STR_MTX_UNLOCK "Error! mutex unlock failed."

typedef struct s_table t_table;

typedef struct s_time
{
	time_t	die;
	time_t	eat;
	time_t	sleep;
	time_t	start_time;
}				t_time;

typedef struct s_mutex
{
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
}				t_mutex;

typedef struct s_philo
{
	int			id;
	t_mutex		mutex;
	t_time		*times;
	t_table		*table;
	time_t		last_meal;
	pthread_t	thread;
}				t_philo;

typedef struct s_table
{
	t_time			times;
	unsigned int	must_eat;
	unsigned int	nb_philos;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	int				stop;
	pthread_t		monitor;
	t_philo			*philo;
}				t_table;

int		msg(char *str, int	exit_nb);
void	free_all(t_table *table);
void	*error_null(char *str);

long	ft_atoi(const char *nptr, int *error);

long	current_time_ms(void);
int		init_table(t_table *table, char **argv);

int		main(int argc, char **argv);

int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		philo_think(t_philo *philo);

void	*routine(void *arg);
void	*monitor_death(void *arg);

int		is_valid_arg(char **argv);

# endif