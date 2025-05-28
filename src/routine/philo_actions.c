/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:37:11 by abouclie          #+#    #+#             */
/*   Updated: 2025/05/28 13:21:31 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	printf("Philosopher %d eating 🍝\n", philo->number);
	usleep(philo->args->time_to_eat * 1000);
	printf("Philosopher %d done eating\n", philo->number);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_sleep()
{
	
}

void	philo_think()
{
	
}