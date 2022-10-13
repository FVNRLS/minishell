/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_dupper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:04:47 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/13 13:42:24 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	reset_stdin_stdout(t_data *data)
{
	dup2(data->fd->std_in, STDIN_FILENO);
	dup2(data->fd->std_out, STDOUT_FILENO);
}

/* 
	sets the exit code depending on the parse_error flag and exception in case
	of exit with signal on heredoc (TERMINATED_BY_CTRL_C).
*/
void	set_global_exit_code(t_data *data)
{
	if (data->parse_error == true)
		g_exit_code = EXIT_FAILURE;
	else if (g_exit_code != TERMINATED_BY_CTRL_C)
		g_exit_code = EXIT_SUCCESS;
}
