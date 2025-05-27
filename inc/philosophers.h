/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:21:19 by abouclie          #+#    #+#             */
/*   Updated: 2025/05/27 09:55:16 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <limits.h>
#include <pthread.h>

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
	pthread_t		philosopher;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	int				meals_eaten;
	long			last_meal_time;
}				t_philo;

typedef struct s_data
{
	t_args	args;
	t_philo	*philo;
}				t_data;

int			check_arg(int argc, char **argv);
int			str_is_digit(char *str);
long int	ft_atoi(const char *nptr, int *error);

#endif