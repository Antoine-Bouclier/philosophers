/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:25:40 by abouclie          #+#    #+#             */
/*   Updated: 2025/05/29 12:08:24 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_someone_dead(t_philo *philo)
{
	long	time_to_die;

	time_to_die = philo->last_meal_time + philo->args->time_to_die;
	if (time_to_die < current_time_ms())
	{
		printf("%d died.💀\n", philo->number);
		return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!is_someone_dead(philo) && *(philo->someone_died) == 0)
	{
		philo_eat(philo);
		philo_think(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
