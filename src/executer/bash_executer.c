/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_executer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:35:16 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/28 18:33:40 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	exec_without_pipe(t_data *data, t_token *token)
{
	extract_cmd_and_path(data, token);
	if (data->exec_error == true)
		return ;
	data->pid = fork();
	if (data->pid < 0)
	{
		perror(NULL);
		free_cmd_and_path(data);
		return;
	}
	else if (data->pid == 0)
		exec_single_cmd(data, token);
	catch_exit_code(data);
	free_cmd_and_path(data);
}

//TODO: edit and check the global
void catch_exit_code(t_data *data)
{
	int	status;

	waitpid(data->pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
}


void	exec_bash_cmd(t_data *data, t_token *token)
{
	printf("--------------------------------------------------\n");
	printf("Before exec:	fd_in:	%d	fd_out:	%d\n", data->fd->in, data->fd->out);
	printf("OUTPUT:\n");
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
	if (data->fd->in != STDIN_FILENO)
		close(data->fd->in);
	if (data->fd->out != STDOUT_FILENO)
		close(data->fd->out);
	data->fd->in = STDIN_FILENO;
	data->fd->out = STDOUT_FILENO;
	printf("After exec:	fd_in:	%d	fd_out:	%d\n", data->fd->in, data->fd->out);
	printf("--------------------------------------------------\n");
}
