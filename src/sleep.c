/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibenne <ibenne@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/05 18:52:58 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/09 00:59:07 by ismo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "philosopher.h"
#include "helpers.h"

time_t	get_duration(t_philosopher *philosopher)
{
	if (philosopher->state == Eating)
		return (philosopher->args->time_to_eat);
	else if (philosopher->state == Sleeping)
		return (philosopher->args->time_to_sleep);
	return (0);
}

void	psleep(t_philosopher *philosopher)
{
	time_t	start;
	time_t	duration;

	start = getms();
	duration = get_duration(philosopher);
	while (duration > 0 && getms() - start < duration)
	{
		if (!*(philosopher->running))
			break ;
		usleep(100);
	}
}
