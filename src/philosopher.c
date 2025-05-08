/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibenne <ibenne@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 13:37:31 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/09 00:50:37 by ismo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "philosopher.h"
#include "helpers.h"

t_philosopher	*construct_philosopher(int id, t_philosopher_args *args)
{
	t_philosopher	*philosopher;

	if (!args)
		return (NULL);
	philosopher = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	philosopher->id = id;
	philosopher->args = args;
	philosopher->state = Thinking;
	philosopher->left = NULL;
	philosopher->right = NULL;
	philosopher->fork = malloc(sizeof(pthread_mutex_t));
	philosopher->time_last_meal = getms();
	if (!philosopher->fork || pthread_mutex_init(philosopher->fork, NULL) != 0)
		return (free(philosopher->fork), NULL);
	return (philosopher);
}

t_philosopher	*create_head_philosopher(t_philosopher_args *args)
{
	t_philosopher	*head;
	bool			*running;

	running = (bool *) malloc(sizeof(bool));
	if (!running)
		return (NULL);
	head = construct_philosopher(1, args);
	if (!head)
		return (free(running), NULL);
	*running = true;
	head->running = running;
	head->time_lock = malloc(sizeof(pthread_mutex_t));
	if (!head->time_lock || pthread_mutex_init(head->time_lock, NULL) != 0)
		return (free(head->time_lock), NULL);
	return (head);
}

t_philosopher	*create_philosophers(t_philosopher_args *args)
{
	t_philosopher	*head;
	t_philosopher	*tail;
	int				p;

	head = create_head_philosopher(args);
	if (!head)
		return (NULL);
	p = 2;
	tail = head;
	while (p <= args->count)
	{
		tail->right = construct_philosopher(p++, args);
		if (!tail->right)
			return (free_philosophers(head), NULL);
		tail->right->time_lock = head->time_lock;
		tail->right->running = head->running;
		tail->right->left = tail;
		tail = tail->right;
	}
	head->left = tail;
	tail->right = head;
	return (head);
}

void	free_philosophers(t_philosopher *philosopher)
{
	int				i;
	int				count;
	t_philosopher	*tmp;

	i = 0;
	count = philosopher->args->count;
	free(philosopher->args);
	free(philosopher->running);
	pthread_mutex_destroy(philosopher->time_lock);
	free(philosopher->time_lock);
	while (philosopher && i < count)
	{
		tmp = philosopher->right;
		pthread_mutex_destroy(philosopher->fork);
		free(philosopher->fork);
		free(philosopher);
		philosopher = tmp;
		i++;
	}
}
