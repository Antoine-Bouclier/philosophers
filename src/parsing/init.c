/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:25:25 by abouclie          #+#    #+#             */
/*   Updated: 2025/05/27 14:00:42 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	int	num = *(int *)arg;
	printf("Philosopher %d is thinking...\n", num);
	usleep(1);
	printf("Philosopher %d is done.\n", num);
	return (NULL);
}

void	init_args(char **argv, t_args *args)
{
	int	error;

	error = 0;
	args->nb_philo = ft_atoi(argv[1], &error);
	args->time_to_die = ft_atoi(argv[2], &error);
	args->time_to_eat = ft_atoi(argv[3], &error);
	args->time_to_sleep = ft_atoi(argv[4], &error);
	if (argv[5])
		args->nb_times_must_eat = ft_atoi(argv[5], &error);
	else
		args->nb_times_must_eat = 0;
	if (error == 1)
		printf("Error! One arguments overflow\n");
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.nb_philo)
	{
		data->philo[i].number = i;
		pthread_mutex_init(&data->philo->right_fork, NULL);
		if (pthread_create(&data->philo->philosopher, NULL, &routine, &data->philo[i]) != 0)
		{
			free_all(data);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < data->args.nb_philo)
	{
		pthread_join(data->philo[i].philosopher, NULL);
		i++;
	}
	return (0);
}
