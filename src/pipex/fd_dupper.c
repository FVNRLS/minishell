/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_dupper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:04:47 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/11 23:17:21 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	reset_stdin_stdout(t_data *data)
{
	dup2(data->fd->std_in, STDIN_FILENO);
	dup2(data->fd->std_out, STDOUT_FILENO);
}

void	set_global_exit_code(t_data *data)
{
	if (data->parse_error == true)
		g_exit_code = EXIT_FAILURE;
	else if (g_exit_code != TERMINATED_BY_CTRL_C)
		g_exit_code = EXIT_SUCCESS;
}
