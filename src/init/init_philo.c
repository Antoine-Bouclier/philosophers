/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:25:25 by abouclie          #+#    #+#             */
/*   Updated: 2025/06/03 12:18:19 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_left_fork(t_philo *philo, int	nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		philo[i].left_fork = &philo[(i + 1) % nb_philo].right_fork;
		i++;
	}
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.nb_philo)
	{
		data->philo[i].number = i;
		data->philo[i].args = &data->args;
		data->philo[i].someone_died = &data->someone_died;
		data->philo[i].error = &data->error;
		data->philo[i].is_eating = 0;
		data->philo[i].last_meal_time = data->start_time;
		data->philo[i].print_mutex = &data->print_mutex;
		data->philo[i].death_mutex = &data->death_mutex;
		data->philo[i].error_mutex = &data->error_mutex;
		pthread_mutex_init(&data->philo[i].right_fork, NULL);
		pthread_mutex_init(&data->philo[i].meal_mutex, NULL);
		i++;
	}
	init_left_fork(data->philo, data->args.nb_philo);
	return (0);
}
