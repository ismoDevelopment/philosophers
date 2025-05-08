/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenne <ibenne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:52:17 by ismo              #+#    #+#             */
/*   Updated: 2025/05/08 18:07:21 by ibenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include "philosopher.h"
#include "helpers.h"

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
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philosopher->id % 2 == 1)
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
	if (!*(philosopher->running))
		return (-1);
	printf("%ld %d has taken a fork\n", getms(), philosopher->id);
	pthread_mutex_lock(second);
	if (!*(philosopher->running))
		return (-1);
	printf("%ld %d has taken a fork\n", getms(), philosopher->id);
	if (!*(philosopher->running))
		return (-1);
	return (0);
}
