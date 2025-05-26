/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:39:16 by abouclie          #+#    #+#             */
/*   Updated: 2025/05/26 12:45:13 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	ft_atoi(const char *nptr, int *error)
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
