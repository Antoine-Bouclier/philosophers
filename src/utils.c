/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:33:50 by abouclie          #+#    #+#             */
/*   Updated: 2025/08/22 08:44:51 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_until(long target_time)
{
	while (current_time_ms() < target_time)
		usleep(100);
}

long	current_time_ms(void)
{
	struct timeval tv;
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
