/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenne <ibenne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:41:21 by ismo              #+#    #+#             */
/*   Updated: 2025/05/08 15:02:17 by ibenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_philosopher	*philosopher;
	long			time;

	philosopher = (t_philosopher *)arg;
	while (philosopher && *(philosopher->running))
	{
		time = getms();
		if (philosopher->state != Done
			&& time - philosopher->time_last_meal
			>= philosopher->args->time_to_die)
		{
			*(philosopher->running) = false;
			printf("%ld %d died\n", time, philosopher->id);
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
	i = 0;
	philosopher = head;
	if (!threads)
		return (NULL);
	threads[head->args->count] = (pthread_t *) malloc(sizeof(pthread_t));
	pthread_create(threads[head->args->count],
		NULL, watcher_thread, philosopher);
	threads[head->args->count + 1] = NULL;
	while (i < head->args->count)
	{
		threads[i] = (pthread_t *) malloc(sizeof(pthread_t));
		if (!threads[i])
			return (free_threads(threads), NULL);
		pthread_create(threads[i], NULL, philosopher_routine, philosopher);
		philosopher = philosopher->right;
		i++;
	}
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
