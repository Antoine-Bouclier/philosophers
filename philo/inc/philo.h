/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 08:41:46 by abouclie          #+#    #+#             */
/*   Updated: 2025/09/01 14:10:40 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define ARG_1 "./philo "
# define ARG_2 "<nb_of_philo> <time_to_die> <time_to_eat> <time_to_sleep> "
# define ARG_3 "optional: <number_of_times_each_philo_must_eat>"

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
	int				eating;
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

int		error_msg(t_table *table, char *str, int ret, int mutex_init);
void	*error_null(t_table *table, char *str, int mutex_init);
void	free_all(t_table *table);

long	current_time_ms(void);
long	ft_atoi(const char *nptr, int *error);
void	usleep_check_death(t_philo *philo, int time_to_wait);

t_table	*init(char **argv);

void	*routine(void *arg);
void	*monitor_death(void *arg);
int		has_stopped(t_table *table);

void	destroy_mutex_forks(pthread_mutex_t	*forks, int last_index);
void	destroy_mutex(t_table *table);

int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		philo_think(t_philo *philo);
int		check_must_eat(t_philo *philo);

void	wait_until(long target_time);

void	*routine_alone(void *arg);
int		start_one_thread(t_table *table);

int		all_philo_eat(t_table *table);

void	set_stop_simulation(t_table *table, int print_mutex);
int		is_someone_dead(t_table *table);

int		alternate_order(t_philo *philo);
int		print_eating(t_philo *philo);
int		update_last_meal(t_philo *philo);

int		init_philo(t_table *table);

#endif