/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenne <ibenne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:55:43 by ismo              #+#    #+#             */
/*   Updated: 2025/05/08 18:08:32 by ibenne           ###   ########.fr       */
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
	if (lock_forks(philosopher) != 0)
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
		if (philo_eat(philosopher) < 0
				|| philo_sleep(philosopher) < 0
				|| philo_think(philosopher) < 0)
				break ;
		usleep(10);
	}
	philosopher->state = Done;
	if (*(philosopher->running) && is_run_complete(philosopher))
		*(philosopher->running) = false;
	return (NULL);
}
