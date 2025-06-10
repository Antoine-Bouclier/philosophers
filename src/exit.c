/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 08:56:25 by abouclie          #+#    #+#             */
/*   Updated: 2025/06/10 14:53:11 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	msg(char *str, int	exit_nb)
{
	printf("%s", str);
	return (exit_nb);
}

void	destroy_mutex(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_destroy(&table->philo[i].mutex.right_fork);
		i++;
	}
	pthread_mutex_destroy(&table->stop_mutex);
	pthread_mutex_destroy(&table->print_mutex);
}

void	*error_null(char *str)
{
	msg(str, EXIT_FAILURE);
	return (NULL);
}

void	free_all(t_table *table)
{
	free(table->philo);
	destroy_mutex(table);
}