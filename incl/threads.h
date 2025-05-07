/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ismo <ismo@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 13:47:07 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/07 23:48:17 by ismo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

void		*philosopher_routine(void *arg);
pthread_t	**create_threads(t_philosopher *head);
void		wait_threads(pthread_t **threads);
void		free_threads(pthread_t **threads);
#endif
