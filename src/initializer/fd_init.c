/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:31:05 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/13 11:28:19 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	init_fd(t_data *data)
{
	data->fd->hdoc = NULL;
	data->fd->in = STDIN_FILENO;
	data->fd->out = STDOUT_FILENO;
	data->fd->hdoc_index = 0;
}

/* 	Saves the standard input and output into fd->std_in and fd->std_out
	in order not to lose the initial STDIN_FILENO and STDOUT_FILENO after
	many redirections and piping during the execution of many commands.
*/
void	dup_stdin_and_stdout(t_data *data)
{
	data->fd->std_in = dup(STDIN_FILENO);
	if (!data->fd->std_in)
	{
		free(data->fd);
		exit(EXIT_FAILURE);
	}
	data->fd->std_out = dup(STDOUT_FILENO);
	if (!data->fd->std_out)
	{
		free(data->fd);
		exit(EXIT_FAILURE);
	}
}
