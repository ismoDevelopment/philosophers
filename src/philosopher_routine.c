/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenne <ibenne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:55:43 by ismo              #+#    #+#             */
/*   Updated: 2025/05/09 14:11:21 by ibenne           ###   ########.fr       */
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

int	philo_eat(t_philosopher *philosopher)
{
	uint64_t	time;

	if (lock_forks(philosopher) != 0)
		return (-1);
	philosopher->state = Eating;
	pthread_mutex_lock(philosopher->time_lock);
	time = getms();
	philosopher->time_last_meal = time;
	pthread_mutex_unlock(philosopher->time_lock);
	printf("%lu %d is eating\n", time, philosopher->id);
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
	printf("%lu %d is sleeping\n", getms(), philosopher->id);
	psleep(philosopher);
	if (!*(philosopher->running))
		return (-1);
	return (0);
}

int	philo_think(t_philosopher *philosopher)
{
	philosopher->state = Thinking;
	printf("%lu %d is thinking\n", getms(), philosopher->id);
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
	if (philosopher->id % 2 == 1)
		usleep(15000);
	while (*(philosopher->running) && (philosopher->args->eat_cycles < 0
			|| cycle < philosopher->args->eat_cycles))
	{
		if (philo_eat(philosopher) < 0
			|| philo_sleep(philosopher) < 0
			|| philo_think(philosopher) < 0)
			break ;
	}
	philosopher->state = Done;
	if (*(philosopher->running) && is_run_complete(philosopher))
		*(philosopher->running) = false;
	return (NULL);
}
