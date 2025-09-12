/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:44:00 by abouclie          #+#    #+#             */
/*   Updated: 2025/09/12 11:04:26 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *philo)
{
	if (has_stopped(philo->table))
		return (1);
	alternate_order(philo, 1);
	if (print_eating(philo) == 1)
	{
		pthread_mutex_unlock(&philo->right_fork->mutex);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		return (1);
	}
	if (update_last_meal(philo))
		return (1);
	usleep_check_death(philo, philo->table->eat_time);
	set_value_mutex(philo->left_fork, 0);
	set_value_mutex(philo->right_fork, 0);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (has_stopped(philo->table))
		return (1);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld %d is sleeping\n", current_time_ms() - philo->table->start_time,
		philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	usleep_check_death(philo, philo->table->sleep_time);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (has_stopped(philo->table))
		return (1);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld %d is thinking\n", current_time_ms() - philo->table->start_time,
		philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	return (0);
}
