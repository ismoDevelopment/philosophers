/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ismo <ismo@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 13:47:02 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/07 14:40:36 by ismo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

t_philosopher_args	*parse_arguments(int argc, char **argv);
bool	is_numeric(char *str);
#endif
