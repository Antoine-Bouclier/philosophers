/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 09:43:45 by abouclie          #+#    #+#             */
/*   Updated: 2025/08/07 10:21:36 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int pq_init(t_priority *pq, int capacity)
{
	pq->queue = malloc(sizeof(t_philo*) * capacity);
	if (!pq->queue)
		return (error_msg("Error during malloc.", 1));
	pq->size = 0;
	pq->capacity = capacity;
	if (pthread_mutex_init(&pq->mutex, NULL) != 0)
		return (1);
	return (0);
}

void pq_push(t_priority *pq, t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&pq->mutex);
	if (pq->size < pq->capacity)
	{
		pq->queue[pq->size] = philo;
		pq->size++;
	}
	i = pq->size - 1;
	while (i > 0)
	{
		if (pq->queue[i]->meals_eaten < pq->queue[i - 1]->meals_eaten)
		{
			t_philo *tmp = pq->queue[i];
			pq->queue[i] = pq->queue[i - 1];
			pq->queue[i - 1] = tmp;
		}
		else
			break ;
		i--;
	}
	pthread_mutex_unlock(&pq->mutex);
}

t_philo	*pq_pop(t_priority *pq)
{
	t_philo	*top;
	int		i;

	pthread_mutex_lock(&pq->mutex);
	if (pq->size == 0)
	{
		pthread_mutex_unlock(&pq->mutex);
		return (NULL);
	}
	top = pq->queue[0];
	i = 1;
	while (i < pq->size)
	{
		pq->queue[i - 1] = pq->queue[i];
		i++;
	}
	pq->size--;
	pthread_mutex_unlock(&pq->mutex);
	return (top);
}

