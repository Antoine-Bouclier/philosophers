/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 08:02:42 by abouclie          #+#    #+#             */
/*   Updated: 2025/08/30 10:44:32 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alternate_order(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->left_fork) != 0)
			return (error_msg(philo->table, STR_MTX_LOCK, 1, 1));
		if (pthread_mutex_lock(philo->right_fork) != 0)
		{
			pthread_mutex_unlock(philo->left_fork);
			return (error_msg(philo->table, STR_MTX_LOCK, 1, 1));
		}
		philo->eating = 1;
	}
	else
	{
		if (pthread_mutex_lock(philo->right_fork) != 0)
			return (error_msg(philo->table, STR_MTX_LOCK, 1, 1));
		if (pthread_mutex_lock(philo->left_fork) != 0)
		{
			pthread_mutex_unlock(philo->right_fork);
			return (error_msg(philo->table, STR_MTX_LOCK, 1, 1));
		}
	}
	return (0);
}

int	print_eating(t_philo *philo)
{
	long	time;

	if (has_stopped(philo->table))
		return (1);
	if (pthread_mutex_lock(&philo->table->print_mutex) != 0)
		return (error_msg(philo->table, STR_MTX_LOCK, 1, 1));
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
	if (pthread_mutex_lock(&philo->meal_mutex) != 0)
		return (error_msg(philo->table, STR_MTX_LOCK, 1, 1));
	philo->last_meal = current_time_ms();
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}
