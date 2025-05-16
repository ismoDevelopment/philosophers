/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenne <ibenne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:47:02 by ismo              #+#    #+#             */
/*   Updated: 2025/05/16 14:50:49 by ibenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int		parse_arguments(int argc,
			char **argv,
			t_philosopher_args *args);
bool	is_numeric(char *str);
#endif
