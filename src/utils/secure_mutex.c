/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouclie <abouclie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:17:45 by abouclie          #+#    #+#             */
/*   Updated: 2025/06/03 12:42:18 by abouclie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	safe_mutex_lock(pthread_mutex_t *mutex, int *error)
{
	if (pthread_mutex_lock(mutex) != 0)
		*error = 1;
	return (*error);
}

int	safe_mutex_unlock(pthread_mutex_t *mutex, int *error)
{
	if (pthread_mutex_unlock(mutex) != 0)
		*error = 1;
	return (*error);
}

