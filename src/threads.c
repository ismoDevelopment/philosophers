/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenne <ibenne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:41:21 by ismo              #+#    #+#             */
/*   Updated: 2025/05/09 15:00:59 by ibenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include "philosopher.h"
#include "philosopher_routine.h"
#include "philosopher_utils.h"
#include "threads.h"
#include "helpers.h"
#include "sleep.h"

void	*watcher_thread(void *arg)
{
	t_philosopher		*philosopher;
	uint64_t			time;
	uint64_t			time_without_meal;

	philosopher = (t_philosopher *)arg;
	while (philosopher && *(philosopher->running))
	{
		pthread_mutex_lock(philosopher->time_lock);
		time = getms();
		time_without_meal = time - philosopher->time_last_meal;
		pthread_mutex_unlock(philosopher->time_lock);
		if (philosopher->state != Done
			&& time_without_meal
			>= philosopher->args->time_to_die)
		{
			pthread_mutex_lock(philosopher->eat_lock);
			print_action(philosopher, ActDied, time);
			*(philosopher->running) = false;
			unlock_all(philosopher);
			break ;
		}
		philosopher = philosopher->right;
	}
	return (NULL);
}

pthread_t	**create_threads(t_philosopher *head)
{
	t_philosopher	*philosopher;
	pthread_t		**threads;
	int				i;

	threads = malloc(sizeof(pthread_t *) * (head->args->count + 2));
	if (!threads)
		return (NULL);
	setzero((void **) threads, head->args->count + 2);
	i = 0;
	philosopher = head;
	while (i < head->args->count)
	{
		threads[i] = (pthread_t *) malloc(sizeof(pthread_t));
		if (!threads[i])
			return (free_threads(threads), NULL);
		if (pthread_create(threads[i],
				NULL, philosopher_routine, philosopher) != 0)
			return (free_threads(threads), NULL);
		philosopher = philosopher->right;
		i++;
	}
	threads[i] = (pthread_t *) malloc(sizeof(pthread_t));
	if (pthread_create(threads[i++], NULL, watcher_thread, philosopher) != 0)
		return (free_threads(threads), NULL);
	return (threads);
}

void	wait_threads(pthread_t **threads)
{
	int	i;

	i = 0;
	while (threads[i])
	{
		pthread_join(*threads[i], NULL);
		i++;
	}
}

void	free_threads(pthread_t **threads)
{
	int	i;

	i = 0;
	while (threads[i])
		free(threads[i++]);
	free(threads);
}
