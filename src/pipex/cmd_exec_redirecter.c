/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_redirecter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:42:29 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/29 12:47:01 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void 	execve_cmd(t_data *data, t_token *token)
{
	if (execve(data->exec->path, data->exec->cmd, data->env) < 0)
	{
		perror(token->content);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void 	exec_single_cmd(t_data *data, t_token *token)
{
	if (data->fd->in != STDIN_FILENO)
	{
		if (dup2(data->fd->in, STDIN_FILENO) < 0)
			exit (EXIT_FAILURE);
		close(data->fd->in);
	}
	if (data->fd->out != STDOUT_FILENO)
	{
		if (dup2(data->fd->out, STDOUT_FILENO) < 0)
			exit (EXIT_FAILURE);
		close(data->fd->out);
	}
	execve_cmd(data, token);
}

void	exec_transitory_cmd(t_data *data, t_token *token)
{
	close(data->pipe[0]);
	if (data->fd->in != STDIN_FILENO)
	{
		if (dup2(data->fd->in, STDIN_FILENO) < 0)
			exit (EXIT_FAILURE);
		close(data->fd->in);
	}
	if (data->fd->out != STDOUT_FILENO)
	{
		if (dup2(data->fd->out, STDOUT_FILENO) < 0)
			exit (EXIT_FAILURE);
		close(data->fd->out);
	}
	else
		dup2(data->pipe[1], STDOUT_FILENO);
	close(data->pipe[1]);
	execve_cmd(data, token);
}

void	exec_last_cmd(t_data *data, t_token *token)
{
	if (data->fd->in != STDIN_FILENO)
	{
		if (dup2(data->fd->in, STDIN_FILENO) < 0)
			exit (EXIT_FAILURE);
		close(data->fd->in);
	}
	if (data->fd->out != STDOUT_FILENO)
	{
		if (dup2(data->fd->out, STDOUT_FILENO) < 0)
			exit (EXIT_FAILURE);
		close(data->fd->out);
	}
	execve_cmd(data, token);
}