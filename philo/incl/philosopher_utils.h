/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_utils.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibenne <ibenne@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 20:58:49 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/12 17:57:52 by ismo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_UTILS_H
# define PHILOSOPHER_UTILS_H

bool	is_running(t_philosopher *philosopher);
bool	can_philosopher_eat(t_philosopher *philosopher);
int		lock_forks(t_philosopher *philosopher);
int		print_action(t_philosopher	*philosopher,
			t_philosopher_action action, time_t timestamp);
void	unlock_all(t_philosopher *philosopher);
bool	is_philosopher_done(t_philosopher *philosopher);
#endif
