/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_routine.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibenne <ibenne@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 23:55:43 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/21 23:10:15 by ismo          ########   odam.nl         */
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

int	lock_forks(t_philosopher *philosopher)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philosopher->id % 2)
	{
		first = philosopher->fork;
		second = philosopher->right->fork;
	}
	else
	{
		first = philosopher->right->fork;
		second = philosopher->fork;
	}
	pthread_mutex_lock(first);
	if (print_action(philosopher, ActFork, getms()) != 0)
		return (pthread_mutex_unlock(first), -1);
	pthread_mutex_lock(second);
	if (print_action(philosopher, ActFork, getms()) != 0)
		return (pthread_mutex_unlock(first),
			pthread_mutex_unlock(second), -1);
	return (0);
}

int	philo_eat(t_philosopher *philosopher)
{
	time_t	time;

	if (lock_forks(philosopher) != 0)
		return (-1);
	pthread_mutex_lock(philosopher->time_lock);
	time = getms();
	philosopher->time_last_meal = time;
	pthread_mutex_unlock(philosopher->time_lock);
	if (print_action(philosopher, ActEat, time) != 0
		|| psleep(philosopher, ActEat) != 0)
		return (pthread_mutex_unlock(philosopher->fork),
			pthread_mutex_unlock(philosopher->right->fork), -1);
	pthread_mutex_unlock(philosopher->fork);
	pthread_mutex_unlock(philosopher->right->fork);
	return (0);
}

int	philo_sleep_think(t_philosopher *philosopher)
{
	if (print_action(philosopher, ActSleep, getms()) != 0
		|| psleep(philosopher, ActSleep) != 0)
		return (-1);
	usleep(1500);
	if (print_action(philosopher, ActThink, getms()) != 0)
		return (-1);
	return (0);
}

void	*philosopher_routine(void *arg)
{
	int				cycle;
	t_philosopher	*philosopher;

	cycle = 0;
	philosopher = (t_philosopher *)arg;
	if (philosopher->args->count <= 1)
		return (NULL);
	while (!is_running(philosopher))
		continue ;
	pthread_mutex_lock(philosopher->time_lock);
	philosopher->time_last_meal = getms();
	pthread_mutex_unlock(philosopher->time_lock);
	if (philosopher->id % 2 == 1)
		usleep(15000);
	while (is_running(philosopher) && (philosopher->args->eat_cycles < 0
			|| cycle < philosopher->args->eat_cycles))
	{
		if (philo_eat(philosopher) < 0 || philo_sleep_think(philosopher) < 0)
			break ;
		cycle++;
	}
	pthread_mutex_lock(philosopher->finish_lock);
	philosopher->done = true;
	pthread_mutex_unlock(philosopher->finish_lock);
	return (NULL);
}
