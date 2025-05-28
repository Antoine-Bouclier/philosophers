/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:11:08 by abouclie          #+#    #+#             */
/*   Updated: 2025/05/28 11:26:54 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.nb_philo)
	{
		if (pthread_create(&data->philo[i].philosopher, NULL, &routine, &data->philo[i]) != 0)
		{
			free_all(data);
			return (1);
		}
		i++;
	}
	return (0);
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
			return (1);
		}
		i++;
	}
	return (0);
}
