/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenne <ibenne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:42:31 by ismo              #+#    #+#             */
/*   Updated: 2025/05/09 14:17:53 by ibenne           ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_philosopher_args	*args;
	t_philosopher		*philosopher;
	pthread_t			**threads;

	(void) argc;
	(void) argv;
	args = parse_arguments(argc, argv);
	if (!args)
		return (1);
	philosopher = create_philosophers(args);
	if (!philosopher)
	{
		printf("Error creating philosophers\n");
		return (free(args), 1);
	}
	threads = create_threads(philosopher);
	if (!threads)
		return (free_philosophers(philosopher), 1);
	wait_threads(threads);
	if (philosopher)
		free_philosophers(philosopher);
	free_threads(threads);
	printf("\n%lu\n", getms());
}
