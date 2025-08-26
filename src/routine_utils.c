/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:14:54 by abouclie          #+#    #+#             */
/*   Updated: 2025/08/26 11:32:55 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	is_someone_dead(t_table *table)
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

int	has_stopped(t_table *table)
{
	int	stopped;

	if (pthread_mutex_lock(&table->simulation_mutex) != 0)
		return (-1);
	stopped = table->simulation_over;
	pthread_mutex_unlock(&table->simulation_mutex);
	return (stopped);
}

void	set_stop_simulation(t_table *table)
{
	if (pthread_mutex_lock(&table->simulation_mutex) != 0)
	{
		pthread_mutex_unlock(&table->print_mutex);
		return ;
	}
	table->simulation_over = 1;
	pthread_mutex_unlock(&table->simulation_mutex);
}
