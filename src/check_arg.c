/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:22:08 by abouclie          #+#    #+#             */
/*   Updated: 2025/08/22 10:47:04 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	is_valid_arg(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!str_is_digit(argv[i]))
			return (error_msg("Wrong format! Digit argument only.", 1));
		i++;
	}
	return (0);
}

int	check_arg(int argc, char **argv)
{
	int	error;

	error = 0;
	if (argc - 1 == 0)
		return (error_msg(STR_ARG, EXIT_FAILURE));
	if (argc - 1 < 4 || argc - 1 > 5)
		return (error_msg("Wrong number of argument (4 or 5)\n"STR_ARG, EXIT_FAILURE));
	if (is_valid_arg(argv))
		return (EXIT_FAILURE);
	if (ft_atoi(argv[1], &error) <= 0)
		return (error_msg(STR_ARG, EXIT_FAILURE));
	return (0);
}