/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ismo <ismo@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 13:41:21 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/07 21:05:11 by ismo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include "philosopher.h"
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
		if (philosopher->state != Eating
			&& philosopher->state != Done
			&& time - philosopher->time_last_meal > philosopher->args->time_to_die)
		{
			*(philosopher->running) = false;
			printf("%ld %ld %d died\n", time, philosopher->time_last_meal, philosopher->id);
			break ;
		}
		philosopher = philosopher->right;
	}
	return (NULL);
}

void	*philosopher_routine(void *arg)
{
	int				cycle;
	t_philosopher	*philosopher;
	long			time;

	cycle = 0;
	philosopher = (t_philosopher *)arg;
	while (*(philosopher->running) && cycle < philosopher->args->eat_cycles)
	{
		pthread_mutex_lock(philosopher->server);
		if (philosopher->right->state != Eating
		&& philosopher->left->state != Eating)
		{
			philosopher->state = Eating;
			pthread_mutex_lock(philosopher->fork);
			printf("%ld %d has taken a fork\n", getms(), philosopher->id);
			pthread_mutex_lock(philosopher->right->fork);
			printf("%ld %d has taken a fork\n", getms(), philosopher->id);
			pthread_mutex_unlock(philosopher->server);
			time = getms();
			printf("%ld %d is eating\n",  time, philosopher->id);
			philosopher->time_last_meal = time;
			psleep(philosopher);
			pthread_mutex_unlock(philosopher->fork);
			pthread_mutex_unlock(philosopher->right->fork);
		}
		else
		{
			pthread_mutex_unlock(philosopher->server);
			usleep(1);
			continue;
		}
		philosopher->state = Sleeping;
		printf("%ld %d is sleeping\n",	getms(), philosopher->id);
		psleep(philosopher);
		if (!*(philosopher->running))
			break;
		philosopher->state = Thinking;
		printf("%ld %d is thinking\n", getms(), philosopher->id);
		cycle++;
	}
	philosopher->state = Done;
	if (is_run_complete(philosopher))
		*(philosopher->running) = false;
	return (NULL);
}

pthread_t **create_threads(t_philosopher *head)
{
	t_philosopher	*philosopher;
	pthread_t		**threads;
	int				i;

	threads = (pthread_t **)malloc(sizeof(pthread_t *) * (head->args->count + 2));
	i = 0;
	philosopher = head;
	if (!threads)
		return (NULL);
	threads[head->args->count] = (pthread_t *) malloc(sizeof(pthread_t));
 	pthread_create(threads[head->args->count], NULL, watcher_thread, philosopher);
	threads[head->args->count + 1] = NULL;
	while (i < head->args->count)
	{
		threads[i] = (pthread_t *) malloc(sizeof(pthread_t));
		if (!threads[i])
			return (free_threads(threads, --i), NULL);
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

void	free_threads(pthread_t **threads, int i)
{
	while (i >= 0)
	{
		free(threads[i]);
		i--;
	}
	free(threads);
}
