/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:25:28 by abouclie          #+#    #+#             */
/*   Updated: 2025/09/12 11:50:05 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(t_table *table, char *str, int ret, int mutex_init)
{
	if (mutex_init)
		destroy_mutex(table);
	if (table != NULL)
		free_all(table);
	printf("%s\n", str);
	return (ret);
}

void	destroy_mutex_forks(t_mutex	*forks, int last_index)
{
	if (last_index > 0)
	{
		while (last_index >= 0)
		{
			pthread_mutex_destroy(&forks[last_index].mutex);
			last_index--;
		}
	}
}

void	destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	if (table->nb_philos > 0)
		destroy_mutex_forks(table->forks, table->nb_philos - 1);
	while (i < table->nb_philos)
	{
		pthread_mutex_destroy(&table->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->simulation_mutex.mutex);
}

void	*error_null(t_table *table, char *str, int mutex_init)
{
	error_msg(table, str, EXIT_FAILURE, mutex_init);
	return (NULL);
}

void	free_all(t_table *table)
{
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
	if (table)
		free(table);
}
