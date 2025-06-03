/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:11:08 by abouclie          #+#    #+#             */
/*   Updated: 2025/06/03 09:30:50 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.nb_philo)
	{
		if (pthread_create(&data->philo[i].philosopher, NULL, &routine, &data->philo[i]) != 0)
		{
			free_all(data);
			data->error = 1;
			return ;
		}
		i++;
	}
	if (pthread_create(&data->monitor, NULL, &monitor_death, data) != 0)
	{
		free_all(data);
		data->error = 1;
		return ;
	}
	if (pthread_join(data->monitor, NULL) != 0)
	{
		free_all(data);
		data->error = 1;
		return ;
	}
}

int	wait_for_threads(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->args.nb_philo)
	{
		if (pthread_join(data->philo[i].philosopher, NULL) != 0)
		{
			free_all(data);
			data->error = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
