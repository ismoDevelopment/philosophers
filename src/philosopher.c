/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ismo <ismo@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 13:37:31 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/07 16:41:53 by ismo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "philosopher.h"
#include "helpers.h"

t_philosopher	*construct_philosopher(int id, t_philosopher_args *args, pthread_mutex_t *server)
{
	t_philosopher	*philosopher;

	if (!args || !server)
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
	philosopher->server = server;
	philosopher->time_last_meal = getms();
	if (!philosopher->fork || pthread_mutex_init(philosopher->fork, NULL) != 0)
		return (pthread_mutex_destroy(philosopher->fork), NULL);
	return (philosopher);
}

t_philosopher	*create_philosophers(t_philosopher_args *args)
{
	t_philosopher	*head;
	t_philosopher	*tail;
	pthread_mutex_t	*server;
	bool			*running;
	int	p;

	p = 1;
	running = (bool *)malloc(sizeof(bool));
	server = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(server, NULL) != 0)
		return (free(running), free(server), NULL);
	head = construct_philosopher(p++, args, server);
	if (!running || !head)
		return (free(running), free(server), NULL);
	*running = true;
	head->running = running;
	tail = head;
	while (p <= args->count)
	{
		tail->right = construct_philosopher(p++, args, server);
		if (!tail->right)
			return (free_philosophers(head), NULL);
		tail->right->running = running;
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
	pthread_mutex_t	*server;

	i = 0;
	server = philosopher->server;
	count = philosopher->args->count;
	while (philosopher && i < count)
	{
		tmp = philosopher->right;
		pthread_mutex_destroy(philosopher->fork);
		free(philosopher->fork);
		free(philosopher);
		philosopher = tmp;
		i++;
	}
	free(server);
}
