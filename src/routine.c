/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:29:20 by abouclie          #+#    #+#             */
/*   Updated: 2025/08/06 11:42:18 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_until(long target_time)
{
	while (current_time_ms() < target_time)
		usleep(100);
}

int	has_stopped(t_table *table)
{
	int	stopped;

	if (pthread_mutex_lock(&table->simulation_mutex) != 0)
		return (-1);
	stopped = table->simulation_over;
	if (pthread_mutex_unlock(&table->simulation_mutex) != 0)
		return (-1);
	return (stopped);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_until(philo->table->start_time);
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

int	is_someone_dead(t_table *table)
{
	int				i;
	long			time_to_die;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_lock(&table->philos[i].meal_mutex) != 0)
			return (error_msg(STR_MTX_LOCK, 1));
		time_to_die = table->philos[i].last_meal + table->die_time;
		if (pthread_mutex_unlock(&table->philos[i].meal_mutex) != 0)
			return (error_msg(STR_MTX_UNLOCK, 1));
		if (time_to_die < current_time_ms())
		{
			if (pthread_mutex_lock(&table->print_mutex) != 0)
				return (error_msg(STR_MTX_LOCK, 1));
			printf("Monitor: philosopher %d is dead. Stopping simulation.\n", table->philos[i].id);
			if (pthread_mutex_unlock(&table->print_mutex) != 0)
				return (error_msg(STR_MTX_UNLOCK, 1));
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
			if (pthread_mutex_lock(&table->simulation_mutex) != 0)
				return (error_null(STR_MTX_LOCK));
			table->simulation_over = 1;
			if (pthread_mutex_unlock(&table->simulation_mutex) != 0)
				return (error_null(STR_MTX_UNLOCK));
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}