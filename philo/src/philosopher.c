/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibenne <ibenne@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 13:37:31 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/12 16:20:09 by ismo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
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
	philosopher->done = false;
	philosopher->args = args;
	philosopher->left = NULL;
	philosopher->right = NULL;
	philosopher->fork = malloc(sizeof(pthread_mutex_t));
	philosopher->time_last_meal = getms();
	if (!philosopher->fork || pthread_mutex_init(philosopher->fork, NULL) != 0)
		return (free_philosophers(philosopher), NULL);
	philosopher->finish_lock = malloc(sizeof(pthread_mutex_t));
	if (!philosopher->finish_lock || pthread_mutex_init(philosopher->finish_lock, NULL) != 0)
		return (free_philosophers(philosopher), NULL);
	philosopher->time_lock = malloc(sizeof(pthread_mutex_t));
	if (!philosopher->time_lock || pthread_mutex_init(philosopher->time_lock, NULL) != 0)
		return (free_philosophers(philosopher), NULL);
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
	head->running_lock = malloc(sizeof(pthread_mutex_t));
	if (!head->running_lock || pthread_mutex_init(head->running_lock, NULL) != 0)
		return (free_philosophers(head), NULL);
	head->server_lock = malloc(sizeof(pthread_mutex_t));
	if (!head->server_lock || pthread_mutex_init(head->server_lock, NULL) != 0)
		return (free_philosophers(head), NULL);
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
		tail->right->running = head->running;
		tail->right->running_lock = head->running_lock;
		tail->right->server_lock = head->server_lock;
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
	free(philosopher->running);
	pthread_mutex_destroy(philosopher->running_lock);
	free(philosopher->running_lock);
	pthread_mutex_destroy(philosopher->server_lock);
	while (philosopher && i < count)
	{
		tmp = philosopher->right;
		pthread_mutex_destroy(philosopher->fork);
		free(philosopher->fork);
		pthread_mutex_destroy(philosopher->finish_lock);
		free(philosopher->finish_lock);
		pthread_mutex_destroy(philosopher->time_lock);
		free(philosopher->time_lock);
		free(philosopher);
		philosopher = tmp;
		i++;
	}
}
