/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:20:23 by abouclie          #+#    #+#             */
/*   Updated: 2025/05/28 14:25:56 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_arg(argc, argv))
		return (1);
	init_args(argv, &data.args);
	data.philo = malloc(sizeof(t_philo) * data.args.nb_philo);
	if (!data.philo)
		return (1);
	pthread_mutex_init(&data.print_mutex, NULL);
	pthread_mutex_init(&data.death_mutex, NULL);
	init_philosophers(&data);
	if (start_thread(&data) != 0)
		return (1);
	if (wait_for_threads(&data) != 0)
		return (1);
	pthread_mutex_destroy(&data.print_mutex);
	pthread_mutex_destroy(&data.death_mutex);
	free_all(&data);
	return (0);
}
