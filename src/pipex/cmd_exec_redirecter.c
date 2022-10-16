/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_redirecter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:42:29 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/13 13:40:37 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/* 
	Executes a non-builtin command with execve function and returns the
	appropriate exit code.
	Resets stdin and stdout back to initial values and prints error message
	in case of parse_error or execution error.
*/
void	exec_bash_cmd(t_data *data)
{
	if (data->exec_error == true)
	{
		reset_stdin_stdout(data);
		exec_error(CMD_NOT_FOUND, data->exec->cmd[0]);
		exit(CMD_NOT_FOUND);
	}
	else
	{
		if (execve(data->exec->path, data->exec->cmd, data->env) < 0)
		{
			reset_stdin_stdout(data);
			exec_error(CMD_NOT_FOUND, data->exec->cmd[0]);
			exit(CMD_NOT_FOUND);
		}
	}
	exit(EXIT_SUCCESS);
}

/* 
	Executes builtins between pipes (all except the last one).
	Closes unused pipes and redirects the standard input into the next pipe.
*/
void	exec_transitory_builtin(t_data *data, int builtin)
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
	g_exit_code = data->builtins->funcs[builtin](data);
	dup2(data->pipe[0], STDIN_FILENO);
	close(data->pipe[1]);
	close(data->pipe[0]);
	dup2(data->fd->std_out, STDOUT_FILENO);
}

/* 
	Executes the last builtin.
	Closes unused pipes and redirects the standard input/output 
	in to the saved std_in and std_out.
*/
void	exec_last_builtin(t_data *data, int builtin)
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
	g_exit_code = data->builtins->funcs[builtin](data);
}

/* 
	Redirects non-builtin command between pipes (all except the last one).
	Closes unused pipes and redirects the standard input into the next pipe.
*/
void	redirect_transitory_cmd(t_data *data)
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
}

/* Redirects the last non-builtin command. */
void	redirect_last_cmd(t_data *data)
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
