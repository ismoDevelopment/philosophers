/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenne <ibenne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:52:58 by ismo              #+#    #+#             */
/*   Updated: 2025/05/20 16:55:48 by ibenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "philosopher.h"
#include "helpers.h"
#include "philosopher_utils.h"

long	get_duration(t_philosopher *philosopher, t_philosopher_action action)
{
	if (action == ActEat)
		return (philosopher->args->time_to_eat * 1000L);
	else if (action == ActSleep)
		return (philosopher->args->time_to_sleep * 1000L);
	return (0);
}

long	get_t_slept(struct timeval start, struct timeval cur_time)
{
	return ((cur_time.tv_sec - start.tv_sec) * 1000000L
		+ (cur_time.tv_usec - start.tv_usec));
}

int	psleep(t_philosopher *philosopher, t_philosopher_action action)
{
	struct timeval	start;
	struct timeval	cur_time;
	long			duration;
	long			remaining;

	gettimeofday(&start, NULL);
	cur_time = start;
	duration = get_duration(philosopher, action);
	while (duration > 0 && get_t_slept(start, cur_time) < duration)
	{
		if (!is_running(philosopher))
			return (-1);
		remaining = duration - get_t_slept(start, cur_time);
		if (remaining > 1000 && usleep(remaining / 2) < 0)
			return (-1);
		gettimeofday(&cur_time, NULL);
	}
	return (0);
}
