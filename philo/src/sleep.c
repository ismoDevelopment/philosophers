/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibenne <ibenne@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/05 18:52:58 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/14 16:31:45 by ismo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "philosopher.h"
#include "helpers.h"
#include "philosopher_utils.h"

time_t	get_duration(t_philosopher *philosopher, t_philosopher_action action)
{
	if (action == ActEat)
		return (philosopher->args->time_to_eat);
	else if (action == ActSleep)
		return (philosopher->args->time_to_sleep);
	return (0);
}

int	psleep(t_philosopher *philosopher, t_philosopher_action action)
{
	time_t	start;
	time_t	duration;

	start = getms();
	duration = get_duration(philosopher, action);
	while (duration > 0 && getms() - start < duration)
	{
		if (!is_running(philosopher))
			return (-1);
		usleep(15000);
	}
	return (0);
}
