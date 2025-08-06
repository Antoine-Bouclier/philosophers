/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:25:28 by abouclie          #+#    #+#             */
/*   Updated: 2025/08/06 11:42:55 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(char *str, int ret)
{
	printf("%s", str);
	return (ret);
}

void	destroy_mutex_forks(pthread_mutex_t	*forks, int last_index)
{
	while (last_index >= 0)
	{
		pthread_mutex_destroy(&forks[last_index]);
		last_index--;
	}
}

void	destroy_mutex(t_table *table)
{
	if (table->nb_philos > 0)
		destroy_mutex_forks(table->forks, table->nb_philos - 1);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->simulation_mutex);
}

void	*error_null(char *str)
{
	error_msg(str, EXIT_FAILURE);
	return (NULL);
}