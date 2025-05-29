/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:37:11 by abouclie          #+#    #+#             */
/*   Updated: 2025/05/29 11:37:25 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	printf("%d has taken a fork\n", philo->number);
	printf("%d has taken a fork\n", philo->number);
	printf("%d is eating 🍝\n", philo->number);
	usleep(philo->args->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo->last_meal_time = current_time_ms();
}

void	philo_sleep(t_philo *philo)
{
	printf("%d is sleeping\n", philo->number);
	usleep(philo->args->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	printf("%d is thinking\n", philo->number);
}
