/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:37:55 by abouclie          #+#    #+#             */
/*   Updated: 2025/06/14 10:46:28 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_until(long target_time)
{
	while (current_time_ms() < target_time)
		usleep(100);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_until(philo->table->times.start_time);
	while (has_stopped(philo->table) == 0)
	{
		if (philo_eat(philo) != 0)
			return (NULL);
		if (philo_sleep(philo) != 0)
			return (NULL);
		if (philo_think(philo) != 0)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}


