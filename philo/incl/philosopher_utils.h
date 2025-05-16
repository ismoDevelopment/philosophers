/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenne <ibenne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:58:49 by ismo              #+#    #+#             */
/*   Updated: 2025/05/16 13:32:22 by ibenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_UTILS_H
# define PHILOSOPHER_UTILS_H

bool	is_running(t_philosopher *philosopher);
bool	can_philosopher_eat(t_philosopher *philosopher);
int		print_action(t_philosopher	*philosopher,
			t_philosopher_action action, time_t timestamp);
bool	is_philosopher_done(t_philosopher *philosopher);
bool	is_all_done(t_philosopher *philosopher);
#endif
