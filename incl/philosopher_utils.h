/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenne <ibenne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:58:49 by ismo              #+#    #+#             */
/*   Updated: 2025/05/09 14:32:19 by ibenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_UTILS_H
# define PHILOSOPHER_UTILS_H

bool	is_run_complete(t_philosopher *philosopher);
bool	can_philosopher_eat(t_philosopher *philosopher);
int		lock_forks(t_philosopher *philosopher);
void	print_action(t_philosopher	*philosopher, t_philosopher_action action);
#endif
