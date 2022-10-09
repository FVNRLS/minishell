/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:43:03 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/09 16:27:57 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "structs.h"

# define SINGLE_QUOTE_MISSING		1
# define DOUBLE_QUOTE_MISSING		2
# define REDIR_SYNTAX_ERROR			3
# define EXIT_ERROR					4
# define CMD_ERROR					5
# define EXIT_ARG_ERROR				6
# define INVALID_PATH				7
# define EXPORT_ERROR				8
# define OLDPWD_ERROR				9
# define UNSET_ERROR				10
# define PATH_ERROR					11
# define PERMISSION_ERROR			12

# define CMD_NOT_FOUND				127
# define INVALID_EXIT_ARG			255
# define TERMINATED_BY_CTRL_C		130
# define PIPE_SYNTAX_ERROR			258

void	print_error(int error);
void	print_token_error(int error, t_token *token);
int		exec_error(int error, char *s);

#endif
