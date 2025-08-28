/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:33:50 by abouclie          #+#    #+#             */
/*   Updated: 2025/08/28 13:19:19 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_until(long target_time)
{
	while (current_time_ms() < target_time)
		usleep(100);
}

int	check_must_eat(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->meal_mutex) != 0)
		return (error_msg(philo->table, STR_MTX_LOCK, 1, 1));
	if (philo->table->must_eat != 0)
	{
		if (philo->meals_eaten == philo->table->must_eat)
		{
			pthread_mutex_unlock(&philo->meal_mutex);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

void	usleep_check_death(t_philo *philo, int time_to_wait)
{
	long	start;
	int		stopped;

	start = current_time_ms();
	while (current_time_ms() - start < time_to_wait)
	{
		stopped = has_stopped(philo->table);
		if (stopped == 1 || stopped == -1)
			break ;
		usleep(500);
	}
}

long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

long	ft_atoi(const char *nptr, int *error)
{
	long int	nb;
	int			isneg;
	int			i;

	nb = 0;
	isneg = 1;
	i = 0;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		isneg *= -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		nb = (nb * 10) + (nptr[i] - '0');
		if ((nb > INT_MAX && isneg == 1) || nb < INT_MIN)
			*error = 1;
		i++;
	}
	nb *= isneg;
	if (nb > INT_MAX || nb < INT_MIN)
		*error = 1;
	return (nb);
}
