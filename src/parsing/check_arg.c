/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:23:51 by abouclie          #+#    #+#             */
/*   Updated: 2025/05/26 09:33:54 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_enough_arg(int argc)
{
	if (argc > 6)
	{
		printf("Too much arguments\n");
		return (1);
	}
	else if (argc < 5)
	{
		printf("Missing arguments\n");
		return (1);
	}
	return (0);
}

static int	is_valid_arg(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!str_is_digit(argv[i]))
		{
			printf("wrong format: \"%s\" must be a number", argv[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_arg(int argc, char **argv)
{
	int	error;

	error = is_enough_arg(argc);
	if (error == 0)
		error = is_valid_arg(argv);
	return (error);
}