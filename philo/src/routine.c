/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:29:20 by abouclie          #+#    #+#             */
/*   Updated: 2025/09/01 14:08:59 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_until(philo->table->start_time);
	if (philo->id % 2)
		usleep(1000);
	while (1)
	{
		if (has_stopped(philo->table) == 1)
			return (NULL);
		if (philo_think(philo) != 0)
			return (NULL);
		if (philo_eat(philo) != 0)
			return (NULL);
		if (philo_sleep(philo) != 0)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

void	*monitor_death(void *arg)
{
	t_table	*table;
	int		dead_idx;

	table = (t_table *)arg;
	while (1)
	{
		dead_idx = is_someone_dead(table);
		if (all_philo_eat(table))
		{
			set_stop_simulation(table, 0);
			return (NULL);
		}
		if (dead_idx >= 0)
		{
			if (pthread_mutex_lock(&table->print_mutex) != 0)
				return (NULL);
			printf("%ld %d died\n", current_time_ms() - table->start_time,
				table->philos[dead_idx].id);
			set_stop_simulation(table, 1);
			pthread_mutex_unlock(&table->print_mutex);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
