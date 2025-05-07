/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ismo <ismo@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/28 11:42:31 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/07 21:05:42 by ismo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

int	main(int argc, char **argv)
{
	t_philosopher_args *args;
	t_philosopher		*philosopher;
	pthread_t			**threads;

	(void) argc;
	(void) argv;
	args = parse_arguments(argc, argv);
	if (!args)
	{
		printf("Error parsing arguments\n");
		return (1);
	}
	philosopher = create_philosophers(args);
	if (!philosopher)
	{
		printf("Error creating philosophers\n");
		return (free(args), 1);
	}
	threads = create_threads(philosopher);
	wait_threads(threads);
}
