/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 09:44:29 by abouclie          #+#    #+#             */
/*   Updated: 2025/08/06 09:15:34 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_argv(t_table *table)
{
	printf("must_eat = %d\n", table->must_eat);
	printf("nb_philo = %d\n", table->nb_philos);
	printf("die_time = %d\n", table->die_time);
	printf("eat_time = %d\n", table->eat_time);
	printf("sleep_time = %d\n", table->sleep_time);
}

void	print_struct(t_table *table)
{
	print_argv(table);
	
}