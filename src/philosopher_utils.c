/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenne <ibenne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:52:17 by ismo              #+#    #+#             */
/*   Updated: 2025/05/08 14:22:07 by ibenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include "philosopher.h"

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
