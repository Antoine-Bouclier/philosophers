/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 08:45:10 by abouclie          #+#    #+#             */
/*   Updated: 2025/06/14 10:47:53 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	has_stopped(t_table *table)
{
	int	stopped;

	if (pthread_mutex_lock(&table->stop_mutex) != 0)
		return (-1);
	stopped = table->stop;
	if (pthread_mutex_unlock(&table->stop_mutex) != 0)
		return (-1);
	return (stopped);
}

int	is_someone_dead(t_table *table)
{
	unsigned int	i;
	long			time_to_die;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_lock(&table->philo[i].mutex.last_meal) != 0)
			return (msg(STR_MTX_LOCK, 1));
		time_to_die = table->philo[i].last_meal + table->philo[i].times->die;
		if (pthread_mutex_unlock(&table->philo[i].mutex.last_meal) != 0)
			return (msg(STR_MTX_UNLOCK, 1));
		if (time_to_die < current_time_ms())
		{
			if (pthread_mutex_lock(&table->print_mutex) != 0)
				return (msg(STR_MTX_LOCK, 1));
			printf("Monitor: philosopher %d is dead. Stopping simulation.\n", table->philo[i].id);
			if (pthread_mutex_unlock(&table->print_mutex) != 0)
				return (msg(STR_MTX_UNLOCK, 1));
			return (1);
		}
		i++;
		usleep(1000);
	}
	return (0);
}

void	*monitor_death(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (is_someone_dead(table))
		{
			if (pthread_mutex_lock(&table->stop_mutex) != 0)
				return (error_null(STR_MTX_LOCK));
			table->stop = 1;
			if (pthread_mutex_unlock(&table->stop_mutex) != 0)
				return (error_null(STR_MTX_UNLOCK));
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

