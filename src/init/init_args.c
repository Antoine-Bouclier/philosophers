/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:24:49 by abouclie          #+#    #+#             */
/*   Updated: 2025/05/28 09:25:02 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
