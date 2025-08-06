/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:44:00 by abouclie          #+#    #+#             */
/*   Updated: 2025/08/06 11:45:42 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	alternate_order(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->left_fork) != 0)
			return (error_msg(STR_MTX_LOCK, 1));
		if (pthread_mutex_lock(philo->right_fork) != 0)
		{
			pthread_mutex_unlock(philo->left_fork);
			return (error_msg(STR_MTX_LOCK, 1));
		}
	}
	else
	{
		if (pthread_mutex_lock(philo->right_fork) != 0)
			return (error_msg(STR_MTX_LOCK, 1));
		if (pthread_mutex_lock(philo->left_fork) != 0)
		{
			pthread_mutex_unlock(philo->right_fork);
			return (error_msg(STR_MTX_LOCK, 1));
		}
	}
	return (0);
}

static int	print_eating(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->table->print_mutex) != 0)
		return (error_msg(STR_MTX_LOCK, 1));
	printf("%d has taken the left fork\n", philo->id);
	printf("%d has taken the right fork\n", philo->id);
	printf("%d is eating\n", philo->id);
	if (pthread_mutex_unlock(&philo->table->print_mutex) != 0)
		return (error_msg(STR_MTX_UNLOCK, 1));
	return (0);
}

static int	check_must_eat(t_philo *philo)
{
	if (philo->table->must_eat != 0)
	{
		if (philo->meals_eaten == philo->table->must_eat)
			return (1);
	}
	return (0);
}

static int	update_last_meal(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->meal_mutex) != 0)
		return (error_msg(STR_MTX_LOCK, 1));
	philo->last_meal = current_time_ms();
	if (pthread_mutex_unlock(&philo->meal_mutex) != 0)
		return (error_msg(STR_MTX_UNLOCK, 1));
	return(0);
}

int	philo_eat(t_philo *philo)
{
	if (check_must_eat(philo) != 0)
		return (1);
	if (has_stopped(philo->table))
		return (1);
	if (alternate_order(philo) == 1)
		return (1);
	if (print_eating(philo) == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	philo->meals_eaten += 1;
	if (update_last_meal(philo))
		return (1);
	usleep(philo->table->eat_time * 1000);
	if (pthread_mutex_unlock(philo->right_fork) != 0)
		return (error_msg(STR_MTX_UNLOCK, 1));
	if (pthread_mutex_unlock(philo->left_fork) != 0)
		return (error_msg(STR_MTX_UNLOCK, 1));
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (check_must_eat(philo) != 0)
		return (1);
	if (has_stopped(philo->table))
		return (1);
	if (pthread_mutex_lock(&philo->table->print_mutex) != 0)
		return (error_msg(STR_MTX_LOCK, 1));
	printf("%d is sleeping\n", philo->id);
	if (pthread_mutex_unlock(&philo->table->print_mutex) != 0)
		return (error_msg(STR_MTX_UNLOCK, 1));
	usleep(philo->table->sleep_time * 1000);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (check_must_eat(philo) != 0)
		return (1);
	if (has_stopped(philo->table))
		return (1);
	if (pthread_mutex_lock(&philo->table->print_mutex) != 0)
		return (error_msg(STR_MTX_LOCK, 1));
	printf("%d is thinking\n", philo->id);
	if (pthread_mutex_unlock(&philo->table->print_mutex) != 0)
		return (error_msg(STR_MTX_UNLOCK, 1));
	return (0);
}
