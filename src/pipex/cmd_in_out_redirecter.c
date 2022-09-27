/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_in_out_redirecter.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:42:29 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/27 19:29:42 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	redirect_first_cmd(t_data *data)
{
	close(data->pipe[0]);
	if (data->fd->in != STDIN_FILENO)
	{
		if (dup_stdin_to_in(data) < 0)
			exit(EXIT_FAILURE);
	}
	if (data->fd->out != STDOUT_FILENO)
	{
		if (dup_stdout_to_out(data) < 0)
			exit(EXIT_FAILURE);
	}
	else
		dup2(data->pipe[1], STDOUT_FILENO);
	close(data->pipe[1]);
}

void	redirect_inter_cmd(t_data *data)
{
	close(data->pipe[0]);
	if (data->fd->in != STDIN_FILENO)
	{
		if (dup_stdin_to_in(data) < 0)
			exit(EXIT_FAILURE);
	}
	else
		dup2(data->pipe[1], STDOUT_FILENO);


	if (data->fd->out != STDOUT_FILENO)
	{
		if (dup_stdout_to_out(data) < 0)
			exit(EXIT_FAILURE);
	}
	else
		dup2(data->pipe[1], STDOUT_FILENO);
	close(data->pipe[1]);
}

void	redirect_last_cmd(t_data *data)
{

}