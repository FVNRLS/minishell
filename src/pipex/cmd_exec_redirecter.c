/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_redirecter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:42:29 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/30 19:14:12 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//TODO: refactor built error name
void exec_bash_cmd(t_data *data)
{
//	int	builtin;
//
//	builtin = ft_get_builtin(data);
//	if (builtin >= 0)
//		exit(EXIT_SUCCESS);
//	else

	if (execve(data->exec->path, data->exec->cmd, data->env) < 0)
	{
		built_error(EXEC_ERROR, data->exec->cmd[0]);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void	redirect_last_builtin(t_data *data)
{
	if (data->fd->in != STDIN_FILENO)
	{
		if (dup2(data->fd->in, STDIN_FILENO) < 0)
		{
			perror(NULL);
			exit (EXIT_FAILURE);
		}
		close(data->fd->in);
	}
	if (data->fd->out != STDOUT_FILENO)
	{
		if (dup2(data->fd->out, STDOUT_FILENO) < 0)
		{
			perror(NULL);
			exit (EXIT_FAILURE);
		}
		close(data->fd->out);
	}
}

void	redirect_transitory_builtin(t_data *data)
{
	if (data->fd->in != STDIN_FILENO)
	{
		if (dup2(data->fd->in, STDIN_FILENO) < 0)
		{
			perror(NULL);
			exit (EXIT_FAILURE);
		}
		close(data->fd->in);
	}
	if (data->fd->out != STDOUT_FILENO)
	{
		if (dup2(data->fd->out, STDOUT_FILENO) < 0)
		{
			perror(NULL);
			exit (EXIT_FAILURE);
		}
		close(data->fd->out);
	}
	else
		dup2(data->pipe[1], STDOUT_FILENO);
}

void	exec_transitory_cmd(t_data *data)
{
	close(data->pipe[0]);
	if (data->fd->in != STDIN_FILENO)
	{
		if (dup2(data->fd->in, STDIN_FILENO) < 0)
		{
			perror(NULL);
			exit (EXIT_FAILURE);
		}
		close(data->fd->in);
	}
	if (data->fd->out != STDOUT_FILENO)
	{
		if (dup2(data->fd->out, STDOUT_FILENO) < 0)
		{
			perror(NULL);
			exit (EXIT_FAILURE);
		}
		close(data->fd->out);
	}
	else
		dup2(data->pipe[1], STDOUT_FILENO);
	close(data->pipe[1]);
//	exec_builtin_or_bash(data);
}

void	exec_last_cmd(t_data *data)
{
	if (data->fd->in != STDIN_FILENO)
	{
		if (dup2(data->fd->in, STDIN_FILENO) < 0)
		{
			perror(NULL);
			exit (EXIT_FAILURE);
		}
		close(data->fd->in);
	}
	if (data->fd->out != STDOUT_FILENO)
	{
		if (dup2(data->fd->out, STDOUT_FILENO) < 0)
		{
			perror(NULL);
			exit (EXIT_FAILURE);
		}
		close(data->fd->out);
	}
//	exec_builtin_or_bash(data);
	close(data->fd->std_in);
}