/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:19:43 by abouclie          #+#    #+#             */
/*   Updated: 2025/09/12 12:01:36 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	thread_philo(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = current_time_ms() + (table->nb_philos * 10);
	while (i < table->nb_philos)
	{
		if (pthread_mutex_lock(&table->philos[i].meal_mutex) != 0)
			return (error_msg(table, STR_MTX_LOCK, 1, 1));
		table->philos[i].last_meal = table->start_time;
		pthread_mutex_unlock(&table->philos[i].meal_mutex);
		if (pthread_create(&table->philos[i].thread, NULL, &routine,
				&table->philos[i]) != 0)
		{
			printf("Error: failed to create a new thread\n");
			break ;
		}
		i++;
	}
	return (i);
}

static int	start_threads(t_table *table)
{
	if (pthread_create(&table->monitor, NULL, &monitor_death, table) != 0)
		return (error_msg(NULL,
				"Error: failed to create a new thread", 1, 0));
	if (pthread_join(table->monitor, NULL) != 0)
		return (error_msg(NULL,
				"Error: failed to join the monitor thread", 1, 0));
	return (0);
}

static int	stop_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (error_msg(NULL, "Error: failed to join thread", 1, 0));
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		ret;
	int		created;
	t_table	*table;

	ret = check_arg(argc, argv);
	if (ret)
		return (ret);
	table = init(argv);
	if (!table)
		return (error_msg(NULL, "Error! Init failed.", 1, 0));
	if (table->nb_philos > 1)
	{
		if (start_threads(table) == 0)
		{
			created = thread_philo(table);
			if (created)
				stop_threads(table);
		}
	}
	else
		start_one_thread(table);
	destroy_mutex(table);
	free_all(table);
	return (ret);
}
