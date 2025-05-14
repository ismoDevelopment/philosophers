/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibenne <ibenne@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 20:52:17 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/14 16:31:26 by ismo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include "philosopher.h"
#include "helpers.h"

bool	is_running(t_philosopher *philosopher)
{
	bool	running;

	pthread_mutex_lock(philosopher->running_lock);
	running = *(philosopher->running);
	pthread_mutex_unlock(philosopher->running_lock);
	return (running);
}

bool	is_philosopher_done(t_philosopher *philosopher)
{
	bool	done;

	pthread_mutex_lock(philosopher->finish_lock);
	done = philosopher->done;
	pthread_mutex_unlock(philosopher->finish_lock);
	return (done);
}

void	unlock_all(t_philosopher *philosopher)
{
	int	i;

	i = 0;
	while (i < philosopher->args->count)
	{
		philosopher = philosopher->right;
		pthread_mutex_unlock(philosopher->fork);
		i++;
	}
	pthread_mutex_unlock(philosopher->time_lock);
}

int	print_action(t_philosopher	*philosopher, t_philosopher_action action,
	time_t timestamp)
{
	const char	*action_str;

	action_str = NULL;
	if (action == ActEat)
		action_str = "is eating";
	if (action == ActSleep)
		action_str = "is sleeping";
	if (action == ActThink)
		action_str = "is thinking";
	if (action == ActFork)
		action_str = "has taken a fork";
	if (action == ActDied)
		action_str = "died";
	if (action != ActDied && !is_running(philosopher))
		return (-1);
	if (!action_str)
		return (0);
	printf("%ld %d %s\n", timestamp, philosopher->id, action_str);
	return (0);
}

int	lock_forks(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->server_lock);
	pthread_mutex_lock(philosopher->fork);
	if (print_action(philosopher, ActFork, getms()) != 0)
		return (-1);
	pthread_mutex_lock(philosopher->right->fork);
	if (print_action(philosopher, ActFork, getms()) != 0)
		return (-1);
	pthread_mutex_unlock(philosopher->server_lock);
	return (0);
}
