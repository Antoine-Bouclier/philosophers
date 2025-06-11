/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 08:57:31 by abouclie          #+#    #+#             */
/*   Updated: 2025/06/11 11:26:29 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	thread_monitor(t_table *table)
{
	if (pthread_create(&table->monitor, NULL, &monitor_death, table) != 0)
		return (1);
	if (pthread_join(table->monitor, NULL) != 0)
	{
		free_all(table);
		return (1);
	}
	return (0);
}

static int	start_threads(t_table *table)
{
	unsigned int	i;

	table->times.start_time = current_time_ms() + (table->nb_philos * 10);
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_lock(&table->philo[i].mutex.last_meal) != 0)
			return (msg(STR_MTX_LOCK, 1));
		table->philo[i].last_meal = current_time_ms();
		if (pthread_mutex_unlock(&table->philo[i].mutex.last_meal) != 0)
			return (msg(STR_MTX_UNLOCK, 1));
		if (pthread_create(&table->philo[i].thread, NULL, &routine, &table->philo[i]) != 0)
			return (msg("Error!, failed to create a new thread", 1));
		i++;
	}
	thread_monitor(table);
	return (0);
}

static int	stop_threads(t_table *table)
{
	unsigned int i;
	
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
			return (msg("Error: failed to join thread", 1));
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc - 1 < 4 || argc - 1 > 5)
		return (msg(STR_ARG, EXIT_FAILURE));
	if (is_valid_arg(argv))
		return (EXIT_FAILURE);
	if (init_table(&table, argv))
		return (EXIT_FAILURE);
	if (start_threads(&table))
	{
		free_all(&table);
		return (EXIT_FAILURE);
	}
	stop_threads(&table);
	free_all(&table);
	return (EXIT_SUCCESS);
}

