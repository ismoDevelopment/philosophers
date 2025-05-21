/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibenne <ibenne@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 11:42:31 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/21 23:19:39 by ismo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "philosopher.h"
#include "helpers.h"
#include "parser.h"
#include "threads.h"

void	clean(t_philosopher	*philosopher,
	pthread_t **philosopher_threads,
	pthread_t *watcher_thread)
{
	printf("Malloc error\n");
	free_philosophers(philosopher);
	if (philosopher_threads)
		free_threads(philosopher_threads);
	if (watcher_thread)
		free(watcher_thread);
}

int	main(int argc, char **argv)
{
	t_philosopher_args	args;
	t_philosopher		*philosopher;
	pthread_t			**philosopher_threads;
	pthread_t			*monitor_thread;

	if (parse_arguments(argc, argv, &args) != 0)
		return (printf("Error parsing arguments\n"), 1);
	philosopher = create_philosophers(&args);
	if (!philosopher)
		return (clean(philosopher, NULL, NULL), 1);
	philosopher_threads = create_philosopher_threads(philosopher);
	if (!philosopher_threads)
		return (clean(philosopher, philosopher_threads, NULL), 1);
	set_running(philosopher, true);
	monitor_thread = (pthread_t *) malloc(sizeof(pthread_t));
	if (!monitor_thread || pthread_create(monitor_thread,
			NULL, watcher_thread, philosopher) != 0)
		return (clean(philosopher, philosopher_threads, monitor_thread), 1);
	pthread_join(*monitor_thread, NULL);
	wait_threads(philosopher_threads);
	if (philosopher)
		free_philosophers(philosopher);
	free_threads(philosopher_threads);
	free(monitor_thread);
}
