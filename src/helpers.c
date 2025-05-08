/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibenne <ibenne@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/29 01:10:16 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/09 00:58:54 by ismo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>

void	setzero(void **array, int n)
{
	int	i;

	i = 0;
	while (i < n)
		array[i++] = NULL;
}

time_t	getms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
