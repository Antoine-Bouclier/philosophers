/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_alone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 08:35:29 by abouclie          #+#    #+#             */
/*   Updated: 2025/08/22 09:04:19 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_alone(void *arg)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)arg;
	wait_until(philo->table->start_time);
	if (pthread_mutex_lock(philo->right_fork) != 0)
	{
		error_msg(STR_MTX_LOCK, 1);
		return (NULL);
	}
	time = current_time_ms() - philo->table->start_time;
	printf("%ld %d has taken a fork\n", time, philo->id);
	usleep(philo->table->die_time * 1000);
	time = current_time_ms() - philo->table->start_time;
	printf("%ld %d died", time, philo->id);
	return (NULL);
}

int	start_one_thread(t_table *table)
{
	table->start_time = current_time_ms() + (table->nb_philos * 10);
	table->philos[0].last_meal = table->start_time;
	if (pthread_create(&table->philos[0].thread, NULL, &routine_alone, &table->philos[0]) != 0)
		return (error_msg("Error!, failed to create a new thread", 1));
	if (pthread_join(table->philos[0].thread, NULL) != 0)
	{
		free_all(table);
		return (error_msg("Error!, failed to join the philosopher", 1));
	}
	return (0);
}