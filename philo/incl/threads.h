/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ismo <ismo@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 13:47:07 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/12 14:23:59 by ismo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

void		*philosopher_routine(void *arg);
pthread_t	**create_philosopher_threads(t_philosopher *head);
pthread_t	*create_watcher_thread(t_philosopher	*philosopher);
void		wait_threads(pthread_t **threads);
void		free_threads(pthread_t **threads);
#endif
