/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:19:43 by abouclie          #+#    #+#             */
/*   Updated: 2025/08/08 08:25:54 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_threads(t_table *table)
{
	int	i;

	table->start_time = current_time_ms() + (table->nb_philos * 10);
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_lock(&table->philos[i].meal_mutex) != 0)
			return (error_msg(STR_MTX_LOCK, 1));
		table->philos[i].last_meal = table->start_time;
		if (pthread_mutex_unlock(&table->philos[i].meal_mutex) != 0)
			return (error_msg(STR_MTX_UNLOCK, 1));
		if (pthread_create(&table->philos[i].thread, NULL, &routine, &table->philos[i]) != 0)
			return (error_msg("Error!, failed to create a new thread", 1));
		i++;
	}
	if (pthread_create(&table->monitor, NULL, &monitor_death, table) != 0)
		return (1);
	if (pthread_join(table->monitor, NULL) != 0)
	{
		free_all(table);
		return (1);
	}
	return (0);
}

static int	stop_threads(t_table *table)
{
	int i;
	
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (error_msg("Error: failed to join thread", 1));
		i++;
	}
	free_all(table);
	return (0);
}

int	main(int argc, char **argv)
{
	int	ret;
	t_table	*table;

	ret = check_arg(argc, argv);
	if (ret)
		return (ret);
	table = init(argv);
	if (!table)
		return (error_msg("Error! Init failed.", 1));
	if (table->nb_philos > 1)
		start_threads(table);
	stop_threads(table);
	return (ret);
}