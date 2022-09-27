/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_executer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:35:16 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/27 19:28:22 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	exec_without_pipe(t_data *data, t_token *token)
{
	extract_cmd_and_path(data, token);
	if (data->exec_error == true)
		return ;
	fork_execution(data, token);
	if (dup_stdin_to_in(data) < 0)
		return ;
	if (dup_stdout_to_out(data) < 0)
		return ;
	catch_exit_code(data);
	ft_cleansplit(data->exec->cmd);
	free(data->exec->path);
	data->exec->path = NULL;
	close(data->fd->in);
	close(data->fd->out);
}

void catch_exit_code(t_data *data)
{
	int	status;

	waitpid(data->pid, &status, 0);
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		if (status != 0)
		{
			data->exec_error = true;
			g_exit_code = EXIT_FAILURE;
		}
	}
}

void	fork_execution(t_data *data, t_token *token)
{
	data->pid = fork();
	if (data->pid < 0)
	{
		perror(NULL);
		data->exec_error = true;
		return ;
	}
	else if (data->pid == 0)
	{
		if (execve(data->exec->path, data->exec->cmd, data->env) < 0)
		{
			perror(token->content);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
}

void	exec_bash_cmd(t_data *data, t_token *token)
{
//	printf("--------------------------------------------------\n");
//	printf("Before exec:	fd_in:	%d	fd_out:	%d\n", data->fd->in, data->fd->out);
//	printf("OUTPUT:\n");
	if (data->exec->last_cmd == 1)
		exec_without_pipe(data, token);
	else
	{
		if (data->exec->cmd_num == 1)
			pipe_first_cmd(data, token);
		else if (data->exec->cmd_num < data->exec->last_cmd)
			pipe_inter_cmd(data, token);
		else if (data->exec->cmd_num == data->exec->last_cmd)
			pipe_last_cmd(data, token);
	}
	data->exec->cmd_num++;

	if (data->exec_error == true)
		return ;

	data->fd->in = STDIN_FILENO;
	data->fd->out = STDOUT_FILENO;
//	printf("After exec:	fd_in:	%d	fd_out:	%d\n", data->fd->in, data->fd->out);
//	printf("--------------------------------------------------\n");
}
