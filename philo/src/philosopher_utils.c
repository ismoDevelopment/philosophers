/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenne <ibenne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:52:17 by ismo              #+#    #+#             */
/*   Updated: 2025/05/16 13:33:45 by ibenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include "philosopher.h"
#include "helpers.h"

void	set_running(t_philosopher *philosopher, bool value)
{
	pthread_mutex_lock(philosopher->running_lock);
	*(philosopher->running) = value;
	pthread_mutex_unlock(philosopher->running_lock);
}

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

bool	is_all_done(t_philosopher *philosopher)
{
	int	n_done;
	int	p;

	n_done = 0;
	p = 0;
	while (philosopher
		&& p < philosopher->args->count
		&& is_philosopher_done(philosopher))
	{
		if (++n_done >= philosopher->args->count)
		{
			return (true);
		}
		philosopher = philosopher->right;
	}
	return (false);
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
