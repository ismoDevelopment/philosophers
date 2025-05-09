/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenne <ibenne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:52:17 by ismo              #+#    #+#             */
/*   Updated: 2025/05/09 14:35:29 by ibenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include "philosopher.h"
#include "helpers.h"

const char *	get_action_str(t_philosopher_action action)
{
	if (action == ActEat)
		return ("is eating");
	if (action == ActSleep)
		return ("is sleeping");
	if (action == ActThink)
		return ("is thinking");
	if (action == ActFork)
		return ("has taken a fork");
	if (action == ActDied)
		return ("died");
	return (NULL);
}

void	print_action(t_philosopher	*philosopher, t_philosopher_action action)
{
	const char	*action_str;

	if (!(*philosopher->running))
		return ;
	action_str = get_action_str(action);
	if (!action_str)
		return ;
	printf("%lu %d %s", getms(), philosopher->id, action_str);
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
	if (!*(philosopher->running))
		return (-1);
	print_action(philosopher, ActFork);
	pthread_mutex_lock(philosopher->right->fork);
	if (!*(philosopher->running))
		return (-1);
	print_action(philosopher, ActFork);
	if (!*(philosopher->running))
		return (-1);
	return (0);
}
