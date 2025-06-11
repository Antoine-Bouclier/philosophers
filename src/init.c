/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 09:53:24 by abouclie          #+#    #+#             */
/*   Updated: 2025/06/11 10:50:29 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	current_time_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

static int	init_times(t_table *table, char **argv)
{
	int	error;

	error = 0;
	table->times.start_time = current_time_ms();
	table->times.die = ft_atoi(argv[2], &error);
	table->times.eat = ft_atoi(argv[3], &error);
	table->times.sleep = ft_atoi(argv[4], &error);
	return (error);
}

static int	init_global_mutex(t_table *table)
{
	if (pthread_mutex_init(&table->stop_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (1);
	return (0);
}

static t_philo	*init_philo(t_table *table)
{
	unsigned int	i;
	t_philo			*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * table->nb_philos);
	while (i < table->nb_philos)
	{
		philo[i].id = i;
		philo[i].times = &table->times;
		if (pthread_mutex_init(&philo[i].mutex.right_fork, NULL) != 0)
			return (error_null("Error! mutex init right fork failed."));
		if (pthread_mutex_init(&philo[i].mutex.last_meal, NULL) != 0)
			return (error_null("Error! mutex init last meal failed."));
		philo[i].last_meal = current_time_ms();
		philo[i].table = table;
		i++;
	}
	i = 0;
	while (i < table->nb_philos)
	{
		philo[i].mutex.left_fork = &philo[(i + 1) % table->nb_philos].mutex.right_fork;
		i++;
	}
	return (philo);
}

int	init_table(t_table *table, char **argv)
{
	if (argv[5])
		table->must_eat = ft_atoi(argv[5], &table->stop);
	table->nb_philos = ft_atoi(argv[1], &table->stop);
	table->stop = 0;
	if (init_times(table, argv))
		return (msg("Error! initialisation of times failed.", 1));
	if (init_global_mutex(table))
		return (msg("Error! global mutex failed.", 1));
	table->philo = init_philo(table);
	if (!table->philo)
		return (1);
	return (0);
}
