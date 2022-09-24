/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_executer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:35:16 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/24 17:41:04 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

static void catch_exit_code(t_data *data)
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

static void	fork_execution(t_data *data, t_token *token)
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
		redirect_in_out(data, token);
		if (execve(data->exec->path, data->exec->cmd, data->env) < 0)
		{
			perror(token->content);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
}

void	execute_with_bash(t_data *data, t_token *token)
{
	extract_cmd_and_path(data, token);
	if (data->exec_error == true)
		return ;
	fork_execution(data, token);
	catch_exit_code(data);
	ft_cleansplit(data->exec->cmd);
	free(data->exec->path);
	data->exec->path = NULL;
}

void	exec_bash_commands(t_data *data)
{
	t_token	*tmp;

	data->exec_error = false;
	if (data->parse_error == true)
		return ;

	tmp = data->tokens;
	resolve_redirections(data);
	merge_words(data);
	tmp = data->tokens;
	if (tmp->flag == T_WORD)
	{
		execute_with_bash(data, tmp);
		if (data->exec_error == true)
			return ;
		close_fd_in_out(data); // must be???
	}

	//printf("fd_in:	%d	fd_out:	%d\n", data->fd->in, data->fd->out);
}