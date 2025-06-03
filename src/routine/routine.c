/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:25:40 by abouclie          #+#    #+#             */
/*   Updated: 2025/06/03 13:38:37 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_someone_dead(t_philo *philo)
{
	long	time_to_die;

	time_to_die = philo->last_meal_time + philo->args->time_to_die;
	if (time_to_die < current_time_ms())
	{
		printf("%d died.💀\n", philo->number);
		return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (*(philo->someone_died) == 0)
	{
		philo_eat(philo);
		philo_think(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	*monitor_death(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	while (data->someone_died == 0)
	{
		i = 0;
		while (i < data->args.nb_philo)
		{
			pthread_mutex_lock(&data->death_mutex);
			if (*(data->philo[i].someone_died) || is_someone_dead(&data->philo[i]))
			{
				data->someone_died = 1;
				pthread_mutex_unlock(&data->death_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->death_mutex);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
