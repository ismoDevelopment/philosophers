/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ismo <ismo@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 13:36:14 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/08 00:33:21 by ismo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include "philosopher.h"

static int	ft_isspace(char c)
{
	return (c == ' '
		|| c == '\f'
		|| c == '\n'
		|| c == '\r'
		|| c == '\t'
		|| c == '\v');
}

static long	ft_atoi(const char *nptr)
{
	long	n;

	n = 0;
	while (ft_isspace(*nptr))
		nptr++;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		n = 10 * n + *nptr - '0';
		nptr++;
	}
	return (n);
}

bool	is_numeric(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

t_philosopher_args *parse_arguments(int argc, char **argv)
{
	t_philosopher_args	*args;

	if (argc < 5 || argc > 6)
		return (NULL);
	args = (t_philosopher_args *)malloc(sizeof(t_philosopher_args));
	if (!args)
		return (NULL);
	if (!is_numeric(argv[1]) || !is_numeric(argv[2]) || !is_numeric(argv[3]) || !is_numeric(argv[4]))
		return (free(args), NULL);
	if (argc == 6 && !is_numeric(argv[5]))
		return (free(args), NULL);
	args->count = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->eat_cycles = 1;
	if (argc == 6)
		args->eat_cycles = ft_atoi(argv[5]);
	return (args);
}
