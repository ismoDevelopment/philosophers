/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_routine.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ismo <ismo@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 23:55:43 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/08 00:25:39 by ismo          ########   odam.nl         */
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

int	philo_eat(t_philosopher *philosopher)
{
	long	time;

	philosopher->state = Eating;
	pthread_mutex_lock(philosopher->fork);
	if (!*(philosopher->running))
		return (-1);
	printf("%ld %d has taken a fork\n", getms(), philosopher->id);
	pthread_mutex_lock(philosopher->right->fork);
	if (!*(philosopher->running))
		return (-1);
	printf("%ld %d has taken a fork\n", getms(), philosopher->id);
	pthread_mutex_unlock(philosopher->server);
	time = getms();
	printf("%ld %d is eating\n", time, philosopher->id);
	psleep(philosopher);
	if (!*(philosopher->running))
		return (-1);
	philosopher->time_last_meal = time;
	pthread_mutex_unlock(philosopher->fork);
	pthread_mutex_unlock(philosopher->right->fork);
	return (0);
}

int	philo_sleep(t_philosopher *philosopher)
{
	philosopher->state = Sleeping;
	printf("%ld %d is sleeping\n", getms(), philosopher->id);
	psleep(philosopher);
	if (!*(philosopher->running))
		return (-1);
	return (0);
}

int	philo_think(t_philosopher *philosopher)
{
	philosopher->state = Thinking;
	printf("%ld %d is thinking\n", getms(), philosopher->id);
	return (0);
}

void	*philosopher_routine(void *arg)
{
	int				cycle;
	t_philosopher	*philosopher;

	cycle = 0;
	philosopher = (t_philosopher *)arg;
	while (*(philosopher->running) && cycle < philosopher->args->eat_cycles)
	{
		pthread_mutex_lock(philosopher->server);
		if (philosopher->args->count > 1
			&& philosopher->right->state != Eating
			&& philosopher->left->state != Eating)
		{
			if (philo_eat(philosopher) < 0 || philo_sleep(philosopher) < 0
				|| philo_think(philosopher) == 0)
				break ;
			cycle++;
			continue ;
		}
		pthread_mutex_unlock(philosopher->server);
		usleep(1);
	}
	philosopher->state = Done;
	if (is_run_complete(philosopher))
		*(philosopher->running) = false;
	return (NULL);
}
