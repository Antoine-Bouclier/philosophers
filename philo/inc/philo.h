/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 08:41:46 by abouclie          #+#    #+#             */
/*   Updated: 2025/09/02 14:18:02 by abouclie         ###   ########.fr       */
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

/* check_arg.c */
int		check_arg(int argc, char **argv);

/* eating.c */
int		alternate_order(t_philo *philo);
int		print_eating(t_philo *philo);
int		update_last_meal(t_philo *philo);

/* exit.c */
int		error_msg(t_table *table, char *str, int ret, int mutex_init);
void	*error_null(t_table *table, char *str, int mutex_init);
void	destroy_mutex_forks(pthread_mutex_t	*forks, int last_index);
void	destroy_mutex(t_table *table);
void	free_all(t_table *table);

/* init_philo.c */
int		init_philo(t_table *table);

/* init.c */
t_table	*init(char **argv);

/* philo_actions.c */
int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		philo_think(t_philo *philo);

/* philo_alone.c */
void	*routine_alone(void *arg);
int		start_one_thread(t_table *table);

/* routine_utils.c */
int		all_philo_eat(t_table *table);
int		is_someone_dead(t_table *table);
int		has_stopped(t_table *table);
void	set_stop_simulation(t_table *table, int print_mutex);

/* routine.c */
void	*routine(void *arg);
void	*monitor_death(void *arg);

/* utils.c */
void	wait_until(long target_time);
int		check_must_eat(t_philo *philo);
void	usleep_check_death(t_philo *philo, int time_to_wait);
long	current_time_ms(void);
long	ft_atoi(const char *nptr, int *error);

#endif