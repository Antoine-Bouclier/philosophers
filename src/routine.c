/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:37:55 by abouclie          #+#    #+#             */
/*   Updated: 2025/06/10 14:56:38 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	must_stop(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->table->stop_mutex) != 0)
		return (msg(STR_MTX_LOCK, 1));
	if (philo->table->stop == 1)
	{
		if (pthread_mutex_unlock(&philo->table->stop_mutex) != 0)
			return (msg(STR_MTX_UNLOCK, 1));
		return (1);
	}
	if (pthread_mutex_unlock(&philo->table->stop_mutex) != 0)
		return (msg(STR_MTX_UNLOCK, 1));
	return (0);
}

static void	eating_routine(t_philo *philo)
{
	while (1)
	{
		if (must_stop(philo))
			break ;
		philo_eat(philo);
		if (must_stop(philo))
			break ;
		philo_sleep(philo);
		if (must_stop(philo))
			break ;
		philo_think(philo);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	eating_routine(philo);
	return (NULL);
}

static int	is_someone_dead(t_philo *philo)
{
	long	time_to_die;

	time_to_die = philo->last_meal + philo->times->die;
	if (time_to_die < current_time_ms())
	{
		if (pthread_mutex_lock(&philo->table->print_mutex) != 0)
			return(msg(STR_MTX_LOCK, 1));
		printf("Monitor: philosopher %d is dead. Stopping simulation.\n", philo->id);
		if (pthread_mutex_unlock(&philo->table->print_mutex) != 0)
			return(msg(STR_MTX_UNLOCK, 1));
		return (1);
	}
	return (0);
}

void	*monitor_death(void *arg)
{
	unsigned int	i;
	t_table			*table;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->nb_philos)
		{
			if (pthread_mutex_lock(&table->stop_mutex) != 0)
				return (error_null(STR_MTX_LOCK));
			if (is_someone_dead(&table->philo[i]))
			{
				table->stop = 1;
				if (pthread_mutex_unlock(&table->stop_mutex) != 0)
					return (error_null(STR_MTX_UNLOCK));
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
