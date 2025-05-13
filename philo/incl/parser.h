/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibenne <ibenne@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/02 13:47:02 by ismo          #+#    #+#                 */
/*   Updated: 2025/05/12 16:16:47 by ismo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

t_philosopher_args	*parse_arguments(int argc, char **argv, t_philosopher_args *args);
bool				is_numeric(char *str);
#endif
