/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibenne <ibenne@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 13:37:48 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/12 17:57:52 by ismo          ########   odam.nl         */
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
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	int			eat_cycles;
}	t_philosopher_args;

typedef struct philosopher
{
	int							id;
	bool						done;
	bool						*running;
	time_t					time_last_meal;
	struct philosopher			*left;
	struct philosopher			*right;
	pthread_mutex_t				*fork;
	pthread_mutex_t				*finish_lock; // lock for setting and reading done boolean - not shared
	pthread_mutex_t				*time_lock; // lock for setting and reading time_last_meal - not shared
	pthread_mutex_t				*running_lock; // lock for when a philosopher has died in the simulation - shared
	t_philosopher_args			*args;
}	t_philosopher;

t_philosopher	*construct_philosopher(int id,
					t_philosopher_args *args);
t_philosopher	*create_philosophers(t_philosopher_args *args);
void			free_philosophers(t_philosopher *philosopher);
#endif
