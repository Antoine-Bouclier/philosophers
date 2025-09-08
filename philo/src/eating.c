/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 08:02:42 by abouclie          #+#    #+#             */
/*   Updated: 2025/09/08 08:32:23 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_value_mutex(t_mutex *mutex, int value)
{
	pthread_mutex_lock(&mutex->mutex);
	if (mutex->value != value)
	{
		mutex->value = value;
		pthread_mutex_unlock(&mutex->mutex);
		return (1);
	}
	pthread_mutex_unlock(&mutex->mutex);
	return (0);
}

static void	odd_order(t_philo *philo, int value)
{
	int	lock;

	lock = 0;
	while (lock == 0 && !has_stopped(philo->table))
	{
		lock = set_value_mutex(philo->right_fork, value);
		if (lock == 1)
		{
			lock = set_value_mutex(philo->right_fork, value);
			if (lock == 0)
			{
				lock = set_value_mutex(philo->left_fork, value);
				if (lock == 0)
					set_value_mutex(philo->right_fork, 0);
			}
		}
		else
			usleep(100);
	}
}

void	alternate_order(t_philo *philo, int value)
{
	int	lock;

	lock = 0;
	if (philo->id % 2 == 0)
	{
		while (lock == 0 && !has_stopped(philo->table))
		{
			lock = set_value_mutex(philo->left_fork, value);
			if (lock == 1)
			{
				lock = set_value_mutex(philo->right_fork, value);
				if (lock == 0)
					set_value_mutex(philo->left_fork, 0);
			}
			else
				usleep(100);
		}
	}
	else
		odd_order(philo, value);
}

int	print_eating(t_philo *philo)
{
	long	time;

	if (has_stopped(philo->table))
		return (1);
	pthread_mutex_lock(&philo->table->print_mutex);
	if (!has_stopped(philo->table))
	{
		time = current_time_ms() - philo->table->start_time;
		printf("%ld %d has taken a fork\n", time, philo->id);
		printf("%ld %d has taken a fork\n", time, philo->id);
		printf("%ld %d is eating\n", time, philo->id);
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
	return (0);
}

int	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = current_time_ms();
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}
