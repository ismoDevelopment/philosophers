/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibenne <ibenne@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 13:37:48 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/22 13:46:08 by ismo          ########   odam.nl         */
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

typedef enum philosopher_action
{
	ActEat,
	ActSleep,
	ActThink,
	ActFork,
	ActDied
}	t_philosopher_action;

typedef struct philosopher_args
{
	int			count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			eat_cycles;
}	t_philosopher_args;

typedef struct philosopher
{
	int							id;
	bool						done;
	bool						*running;
	time_t						time_last_meal;
	struct philosopher			*left;
	struct philosopher			*right;
	pthread_mutex_t				*fork;
	pthread_mutex_t				*finish_lock;
	pthread_mutex_t				*time_lock;
	pthread_mutex_t				*running_lock;
	t_philosopher_args			*args;
}	t_philosopher;

t_philosopher	*create_philosophers(t_philosopher_args *args);
void			free_philosophers(t_philosopher *philosopher);
void			set_running(t_philosopher *philosopher, bool value);
#endif
