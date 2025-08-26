/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:29:20 by abouclie          #+#    #+#             */
/*   Updated: 2025/08/26 10:08:07 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	has_stopped(t_table *table)
{
	int	stopped;

	if (pthread_mutex_lock(&table->simulation_mutex) != 0)
		return (-1);
	stopped = table->simulation_over;
	pthread_mutex_unlock(&table->simulation_mutex);
	return (stopped);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_until(philo->table->start_time);
	while (has_stopped(philo->table) == 0)
	{
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

int is_someone_dead(t_table *table)
{
	int		i;
	long	time_to_die;

	i = 0;
	while (i < table->nb_philos)
	{
		if (check_must_eat(&table->philos[i]))
			break ;
		if (pthread_mutex_lock(&table->philos[i].meal_mutex) != 0)
			return (-2);
		time_to_die = table->philos[i].last_meal + table->die_time;
		pthread_mutex_unlock(&table->philos[i].meal_mutex);
		if (time_to_die < current_time_ms())
			return (i);
		i++;
	}
	return (-1);
}

int	all_philo_eat(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (!check_must_eat(&table->philos[i]))
			return (0);
		i++;
	}
	return (1);
}

void *monitor_death(void *arg)
{
	t_table	*table;
	int		dead_idx;

	table = (t_table *)arg;
	while (1)
	{
		dead_idx = is_someone_dead(table);
		if (all_philo_eat(table))
		{
			if (pthread_mutex_lock(&table->simulation_mutex) != 0)
			{
				pthread_mutex_unlock(&table->print_mutex);
				return (NULL);
			}
			table->simulation_over = 1;
			pthread_mutex_unlock(&table->simulation_mutex);
			return (NULL);
		}
		if (dead_idx >= 0)
		{
			if (pthread_mutex_lock(&table->print_mutex) != 0)
				return (NULL);
			printf("%ld %d died\n", current_time_ms() - table->start_time,
				table->philos[dead_idx].id);
			if (pthread_mutex_lock(&table->simulation_mutex) != 0)
			{
				pthread_mutex_unlock(&table->print_mutex);
				return (NULL);
			}
			table->simulation_over = 1;
			pthread_mutex_unlock(&table->print_mutex);
			pthread_mutex_unlock(&table->simulation_mutex);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
