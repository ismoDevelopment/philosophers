/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenne <ibenne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:55:43 by ismo              #+#    #+#             */
/*   Updated: 2025/05/08 15:07:06 by ibenne           ###   ########.fr       */
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
	if (!*(philosopher->running))
		return (-1);
	time = getms();
	printf("%ld %d is eating\n", time, philosopher->id);
	philosopher->time_last_meal = time;
	psleep(philosopher);
	if (!*(philosopher->running))
		return (-1);
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
	usleep(1000);
	if (!*(philosopher->running))
		return (-1);
	return (0);
}

void	*philosopher_routine(void *arg)
{
	int				cycle;
	t_philosopher	*philosopher;

	cycle = 0;
	philosopher = (t_philosopher *)arg;
	while (*(philosopher->running) && (philosopher->args->eat_cycles < 0
			|| cycle < philosopher->args->eat_cycles))
	{
		pthread_mutex_lock(philosopher->server);
		if (can_philosopher_eat(philosopher))
		{
			if (philo_eat(philosopher) < 0
				|| philo_sleep(philosopher) < 0
				|| philo_think(philosopher) < 0)
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
