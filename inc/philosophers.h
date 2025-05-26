/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:21:19 by abouclie          #+#    #+#             */
/*   Updated: 2025/05/26 13:28:32 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <limits.h>
#include <pthread.h>

typedef struct s_fork
{
	pthread_mutex_t	fork;
}				t_fork;

typedef struct s_philo
{
	int				number;
	pthread_t		philosopher;
	t_fork			*right_fork;
	t_fork			*left_fork;
	struct s_philo	*next;
}				t_philo;

typedef struct s_data
{
	int	number_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_each_must_eat;
	t_philo		**philosophers;
}				t_data;

int	check_arg(int argc, char **argv);
int	str_is_digit(char *str);

#endif