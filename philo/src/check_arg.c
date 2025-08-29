/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 08:22:08 by abouclie          #+#    #+#             */
/*   Updated: 2025/08/29 10:51:31 by abouclie         ###   ########.fr       */
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
			return (error_msg(NULL
					, "Wrong format! Positive digit argument only.", 1, 0));
		i++;
	}
	return (0);
}

int	check_arg(int argc, char **argv)
{
	int	error;

	error = 0;
	if (argc - 1 == 0)
		return (error_msg(NULL, ARG_1 ARG_2 ARG_3, EXIT_FAILURE, 1));
	if (argc - 1 < 4 || argc - 1 > 5)
		return (error_msg(NULL, "Wrong number of argument (4 or 5)\n"
				ARG_1 ARG_2 ARG_3, EXIT_FAILURE, 0));
	if (is_valid_arg(argv))
		return (EXIT_FAILURE);
	if (ft_atoi(argv[1], &error) <= 0)
		return (error_msg(NULL, ARG_1 ARG_2 ARG_3, EXIT_FAILURE, 0));
	return (0);
}
