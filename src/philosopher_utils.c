/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenne <ibenne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:52:17 by ismo              #+#    #+#             */
/*   Updated: 2025/05/09 15:03:12 by ibenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include "philosopher.h"
#include "helpers.h"

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
	pthread_mutex_unlock(philosopher->eat_lock);
	pthread_mutex_unlock(philosopher->time_lock);
}

int	print_action(t_philosopher	*philosopher, t_philosopher_action action,
	uint64_t timestamp)
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
	if (!(*philosopher->running))
		return (-1);
	if (!action_str)
		return (0);
	printf("%lu %d %s\n", timestamp, philosopher->id, action_str);
	return (0);
}

bool	is_run_complete(t_philosopher *philosopher)
{
	int	i;

	i = 0;
	while (i < philosopher->args->count)
	{
		if (philosopher->state != Done)
			return (false);
		philosopher = philosopher->right;
		i++;
	}
	return (true);
}

bool	can_philosopher_eat(t_philosopher *philosopher)
{
	return (philosopher->running
		&& philosopher->args->count > 1
		&& philosopher->right->state != Eating
		&& philosopher->left->state != Eating);
}

int	lock_forks(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->fork);
	if (print_action(philosopher, ActFork, getms()) != 0)
		return (-1);
	pthread_mutex_lock(philosopher->right->fork);
	if (print_action(philosopher, ActFork, getms()) != 0)
		return (-1);
	return (0);
}
