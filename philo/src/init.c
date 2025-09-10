/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:20:36 by abouclie          #+#    #+#             */
/*   Updated: 2025/09/10 10:52:20 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	argv_to_struct(char **argv, t_table *table)
{
	int	error;

	error = 0;
	table->must_eat = -1;
	if (argv[5])
		table->must_eat = ft_atoi(argv[5], &error);
	table->nb_philos = ft_atoi(argv[1], &error);
	table->die_time = ft_atoi(argv[2], &error);
	table->eat_time = ft_atoi(argv[3], &error);
	table->sleep_time = ft_atoi(argv[4], &error);
	table->think_time = 0;
	if (table->die_time - (table->eat_time + table->sleep_time) > 1)
		table->think_time = (table->die_time
				- (table->eat_time + table->sleep_time)) - 1;
	return (error);
}

static int	init_mutex(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->simulation_mutex.mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&table->simulation_mutex.mutex);
		return (1);
	}
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&table->forks[i].mutex, NULL) != 0)
		{
			destroy_mutex_forks(table->forks, i);
			pthread_mutex_destroy(&table->print_mutex);
			pthread_mutex_destroy(&table->simulation_mutex.mutex);
			return (1);
		}
		table->forks[i].value = 0;
		i++;
	}
	return (0);
}

static int	init_table(t_table *table)
{
	table->simulation_mutex.value = 0;
	table->forks = malloc(sizeof(t_mutex) * table->nb_philos);
	if (!table->forks)
		return (1);
	if (init_mutex(table))
	{
		free(table->forks);
		return (1);
	}
	table->philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (!table->philos)
	{
		destroy_mutex(table);
		free(table->forks);
		return (1);
	}
	if (init_philo(table))
	{
		free(table->forks);
		free(table->philos);
		return (1);
	}
	return (0);
}

t_table	*init(char **argv)
{
	t_table	*table;
	int		ret;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	ret = argv_to_struct(argv, table);
	if (ret)
	{
		free(table);
		return (NULL);
	}
	if (init_table(table))
	{
		free(table);
		return (NULL);
	}
	return (table);
}
