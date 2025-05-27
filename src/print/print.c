/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:47:00 by abouclie          #+#    #+#             */
/*   Updated: 2025/05/27 14:09:58 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_args(t_args *args)
{
	printf("numbers of philo: %d\n", args->nb_philo);
	printf("time to die: %d\n", args->time_to_die);
	printf("time to eat: %d\n", args->time_to_eat);
	printf("time to sleep: %d\n", args->time_to_sleep);
	printf("number of times each philosopher must eat: %d\n", args->nb_times_must_eat);
}

void	print_philo(t_philo *philo)
{
	printf("philo number: %d", philo->number);
}