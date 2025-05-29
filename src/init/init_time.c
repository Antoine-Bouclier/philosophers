/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:58:48 by abouclie          #+#    #+#             */
/*   Updated: 2025/05/29 11:26:15 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	current_time_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

/* int test()
{
	struct timeval tv;
	struct timeval tv2;

	if (gettimeofday(&tv, NULL) == 0)
	{
		printf("Seconds: %ld\n", tv.tv_sec);
		printf("Microseconds: %ld\n", tv.tv_usec);
		long int start_time = (tv.tv_sec * 1000L) + (tv.tv_usec / 1000L);
		printf("start time: %ld\n", start_time);
		usleep(10000);
		gettimeofday(&tv2, NULL);
		long int end_time = (tv2.tv_sec * 1000L) + (tv2.tv_usec / 1000L);
		printf("end time: %ld\n", end_time);
		long int difference = end_time - start_time;
		printf("difference: %ld\n", difference);
	}
	else
	{
		perror("gettimeofday");
	}
	return 0;
} */