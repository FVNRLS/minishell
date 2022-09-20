/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:43:03 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/19 19:05:59 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

#ifndef ERRORS_H
# define ERRORS_H

# define SINGLE_QUOTE_MISSING		1
# define DOUBLE_QUOTE_MISSING		2
# define REDIR_SYNTAX_ERROR			3
# define PIPE_SYNTAX_ERROR			4
# define OPEN_ERROR					5
# define CREATE_ERROR				6
# define EXIT_ERROR					7
# define CMD_ERROR					8
# define EXIT_ARG_ERROR				9
# define INVALID_PATH				10
# define CD_ARG_ERROR				11

void	print_error(int error);
void	print_token_error(int error, t_token *token);

#endif
