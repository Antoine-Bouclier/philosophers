/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:44:00 by abouclie          #+#    #+#             */
/*   Updated: 2025/06/10 14:55:18 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	alternate_order(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->mutex.left_fork) != 0)
			return (msg(STR_MTX_LOCK, 1));
		if (pthread_mutex_lock(&philo->mutex.right_fork) != 0)
		{
			pthread_mutex_unlock(philo->mutex.left_fork);
			return (msg(STR_MTX_LOCK, 1));
		}
	}
	else
	{
		if (pthread_mutex_lock(&philo->mutex.right_fork) != 0)
			return (msg(STR_MTX_LOCK, 1));
		if (pthread_mutex_lock(philo->mutex.left_fork) != 0)
		{
			pthread_mutex_unlock(&philo->mutex.right_fork);
			return (msg(STR_MTX_LOCK, 1));
		}
	}
	return (0);
}

static int	print_eating(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->table->print_mutex) != 0)
		return (msg(STR_MTX_LOCK, 1));
	printf("%d has taken the left fork\n", philo->id);
	printf("%d has taken the right fork\n", philo->id);
	printf("%d is eating\n", philo->id);
	if (pthread_mutex_unlock(&philo->table->print_mutex) != 0)
		return (msg(STR_MTX_UNLOCK, 1));
	return (0);
}

int	philo_eat(t_philo *philo)
{
	if (alternate_order(philo) == 1)
		return (1);
	if (print_eating(philo) == 1)
	{
		pthread_mutex_unlock(&philo->mutex.right_fork);
		pthread_mutex_unlock(philo->mutex.left_fork);
		return (1);
	}
	usleep(philo->times->eat * 1000);
	if (pthread_mutex_unlock(&philo->mutex.right_fork) != 0)
		return (msg(STR_MTX_UNLOCK, 1));
	if (pthread_mutex_unlock(philo->mutex.left_fork) != 0)
		return (msg(STR_MTX_UNLOCK, 1));
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->table->print_mutex) != 0)
		return (msg(STR_MTX_LOCK, 1));
	printf("%d is sleeping\n", philo->id);
	if (pthread_mutex_unlock(&philo->table->print_mutex) != 0)
		return (msg(STR_MTX_UNLOCK, 1));
	usleep(philo->times->sleep * 1000);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->table->print_mutex) != 0)
		return (msg(STR_MTX_LOCK, 1));
	printf("%d is thinking\n", philo->id);
	if (pthread_mutex_unlock(&philo->table->print_mutex) != 0)
		return (msg(STR_MTX_UNLOCK, 1));
	return (0);
}