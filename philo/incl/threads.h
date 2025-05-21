/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibenne <ibenne@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 13:47:07 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/21 23:19:21 by ismo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

void		*philosopher_routine(void *arg);
pthread_t	**create_philosopher_threads(t_philosopher *head);
pthread_t	*create_watcher_thread(t_philosopher	*philosopher);
void		wait_threads(pthread_t **threads);
void		free_threads(pthread_t **threads);
void		*watcher_thread(void *arg);
#endif
