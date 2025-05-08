/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenne <ibenne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:52:58 by ismo              #+#    #+#             */
/*   Updated: 2025/05/08 15:03:52 by ibenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "philosopher.h"
#include "helpers.h"

long	get_duration(t_philosopher *philosopher)
{
	if (philosopher->state == Eating)
		return (philosopher->args->time_to_eat);
	else if (philosopher->state == Sleeping)
		return (philosopher->args->time_to_sleep);
	return (0);
}

void	psleep(t_philosopher *philosopher)
{
	long	start;
	long	duration;

	start = getms();
	duration = get_duration(philosopher);
	while (duration > 0 && getms() - start < duration)
	{
		if (!*(philosopher->running))
			break ;
		usleep(100);
	}
}
