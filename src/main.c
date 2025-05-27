/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:20:23 by abouclie          #+#    #+#             */
/*   Updated: 2025/05/27 09:32:44 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	int	error;

	if (check_arg(argc, argv))
		return (1);
	int	n = ft_atoi(argv[1], &error);
	if (n < 2)
	{
		printf("Error: at least 2 philosophers are needed.\n");
		return (1);
	}
	return (0);
}
