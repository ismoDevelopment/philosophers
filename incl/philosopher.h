/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenne <ibenne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:37:48 by ismo              #+#    #+#             */
/*   Updated: 2025/05/08 18:11:54 by ibenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

typedef enum philosopher_state
{
	Eating,
	Sleeping,
	Thinking,
	Done
}	t_philosopher_state;

typedef struct philosopher_args
{
	int				count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				eat_cycles;
}	t_philosopher_args;

typedef struct philosopher
{
	int							id;
	bool						*running;
	long						time_last_meal;
	struct philosopher			*left;
	struct philosopher			*right;
	pthread_mutex_t				*fork;
	t_philosopher_args			*args;
	t_philosopher_state			state;
}	t_philosopher;

t_philosopher	*construct_philosopher(int id,
					t_philosopher_args *args);
t_philosopher	*create_philosophers(t_philosopher_args *args);
void			free_philosophers(t_philosopher *philosopher);
#endif
