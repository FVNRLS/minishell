/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:43:03 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/04 14:31:44 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

#ifndef ERRORS_H
# define ERRORS_H

# define SINGLE_QUOTE_MISSING		1
# define DOUBLE_QUOTE_MISSING		2
# define REDIR_SYNTAX_ERROR			3
# define PIPE_SYNTAX_ERROR			4
# define EXIT_ERROR					5
# define CMD_ERROR					6
# define EXIT_ARG_ERROR				7
# define INVALID_PATH				8
# define EXPORT_ERROR				9
# define EXPORT_FLAG				10
# define UNSET_FLAG					11
# define UNSET_ERROR				12
# define EXEC_ERROR					13
# define PATH_ERROR					14

void	print_error(int error);
void	print_token_error(int error, t_token *token);
int 	built_error(int error, char *s);

#endif
