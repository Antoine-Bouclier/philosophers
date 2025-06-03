/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:37:11 by abouclie          #+#    #+#             */
/*   Updated: 2025/06/03 13:47:26 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	alternate_order(t_philo *philo)
{
	if (philo->number % 2)
	{
		if (!safe_mutex_lock(&philo->right_fork, philo->error))
			return (1);
		if (!safe_mutex_lock(philo->left_fork, philo->error))
			return (1);
	}
	else
	{
		if (!safe_mutex_lock(philo->left_fork, philo->error))
			return (1);
		if (!safe_mutex_lock(&philo->right_fork, philo->error))
			return (1);
	}
	return (0);
}

static int	check_should_stop(t_philo *philo)
{
	safe_mutex_lock(philo->error_mutex, philo->error);
	safe_mutex_lock(philo->death_mutex, philo->error);
	if (*(philo->error) != 0 || *(philo->someone_died) != 0)
	{
		safe_mutex_unlock(philo->error_mutex, philo->error);
		safe_mutex_unlock(philo->death_mutex, philo->error);
		return (1);
	}
	safe_mutex_unlock(philo->error_mutex, philo->error);
	safe_mutex_unlock(philo->death_mutex, philo->error);
	return (0);
}

static void	eating(t_philo *philo)
{
	safe_mutex_lock(philo->print_mutex, philo->error);
	printf("%d has taken a fork\n", philo->number);
	printf("%d has taken a fork\n", philo->number);
	printf("%d is eating 🍝\n", philo->number);
	*(philo->error) = safe_mutex_unlock(philo->print_mutex, philo->error);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = current_time_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	usleep(philo->args->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

int	philo_eat(t_philo *philo)
{
	if(!check_should_stop(philo))
		return (1);
	if (!alternate_order(philo))
	{
		*(philo->error) = 1;
		write(2, "Error: mutex lock failed in philo_eat\n", 38);
		return (1);
	}
	eating(philo);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if(!check_should_stop(philo))
		return (1);
	safe_mutex_lock(philo->print_mutex, philo->error);
	if (*(philo->error) != 0)
	printf("%d is sleeping\n", philo->number);
	safe_mutex_lock(philo->print_mutex, philo->error);
	usleep(philo->args->time_to_sleep * 1000);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if(!check_should_stop(philo))
		return (1);
	pthread_mutex_lock(philo->print_mutex);
	printf("%d is thinking\n", philo->number);
	pthread_mutex_unlock(philo->print_mutex);
	return (0);
}
