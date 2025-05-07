/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ismo <ismo@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/05 18:52:58 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/08 00:15:18 by ismo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "philosopher.h"
#include "helpers.h"

size_t	get_duration(t_philosopher *philosopher)
{
	if (philosopher->state == Eating)
		return (philosopher->args->time_to_eat);
	else if (philosopher->state == Sleeping)
		return (philosopher->args->time_to_sleep);
	return (0);
}

void	psleep(t_philosopher *philosopher)
{
	size_t	time;
	size_t	start;
	size_t	duration;

	start = getms();
	time = start;
	duration = get_duration(philosopher);
	while (duration > 0 && time - start < philosopher->args->time_to_sleep)
	{
		if (!*(philosopher->running))
			break ;
		time += 10;
		usleep(10);
	}
}
