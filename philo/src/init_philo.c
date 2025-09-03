/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:09:54 by abouclie          #+#    #+#             */
/*   Updated: 2025/09/03 09:58:11 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&table->philos[i].meal_mutex, NULL) != 0)
		{
			if (i > 0)
			{
				while (i--)
					pthread_mutex_destroy(&table->philos[i].meal_mutex);
			}
			destroy_mutex_forks(table->forks, table->nb_philos - 1);
			pthread_mutex_destroy(&table->print_mutex);
			pthread_mutex_destroy(&table->simulation_mutex.mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].table = table;
		if (init_mutex_philo(table))
			return (1);
		table->philos[i].right_fork = &table->forks[i];
		if (table->nb_philos > 1)
			table->philos[i].left_fork = &table->forks[(i
					+ table->nb_philos - 1) % table->nb_philos];
		else
			table->philos[i].left_fork = NULL;
		i++;
	}
	return (0);
}
