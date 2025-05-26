/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:21:19 by abouclie          #+#    #+#             */
/*   Updated: 2025/05/26 13:15:24 by abouclie         ###   ########.fr       */
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

int	check_arg(int argc, char **argv);
int	str_is_digit(char *str);

#endif