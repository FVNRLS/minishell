/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:47:27 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/17 11:40:51 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	free_cmd_and_path(t_data *data)
{
	ft_cleansplit(data->exec->cmd);
	data->exec->cmd = NULL;
	free(data->exec->path);
	data->exec->path = NULL;
}

/*
	Extracts the cmd and path based on the following cases:
	
	1) Absolute or relative path is given:
		extracts the path from the given input.
		searches for the appropriate cmd in PATH env and saves it as exec->cmd.
	
	2) Only the command name is given:
		searches for the appropriate cmd in PATH env and saves it as cmd with
		another arguments (next word tokens).
		Then also adds the found path to exec->path.
*/
static void	extract_cmd_and_path(t_data *data, t_token *token)
{
	if (data->exec->no_cmd == true || !data->tokens->content)
		return ;
	if (token->content[0] == '.' || token->content[0] == SLASH)
	{
		data->exec->cmd = extract_cmd_from_path(data);
		if (!data->exec->cmd || !data->exec->path)
		{
			data->exec_error = true;
			return ;
		}
	}
	else
	{
		data->exec->cmd = get_cmd(data);
		if (data->exec_error == true)
			return ;
		data->exec->path = get_cmd_path(data);
		if (!data->exec->path)
			data->exec_error = true;
	}
}

/*
	Extracts the cmd and path and executes the given token (cmd).
	Redirects the cmd input/output based on the cmd number.
*/
static void	exec_cmd(t_data *data, t_token *token)
{
	extract_cmd_and_path(data, token);
	if (data->exec->cmd_num < data->exec->last_cmd)
		pipe_transitory_cmd(data);
	else if (data->exec->cmd_num == data->exec->last_cmd)
		pipe_last_cmd(data);
	free_cmd_and_path(data);
}

/* reset parameters to initial values. */
static void	reset_params(t_data *data)
{
	data->parse_error = false;
	data->exec_error = false;
	data->exec->no_cmd = false;
	data->fd->in = STDIN_FILENO;
	data->fd->out = STDOUT_FILENO;
}

/*
	Algorithm for executing commands, separated with pipes.

	Given are at the beginning tokens with already merged 
	redirections.
	First the redirections are resolved. As a result we get
	the final input fd_in and output fd_out.
	After that a command is built from all word tokens until the pipe/end.
	The command is executed and redirected until the next pipe 
	over the desired input/output.
 	All word tokens are immediately deleted after execution.
	At the end the allocated heredoc-files are deleted and freed.
*/
void	execute_tokens(t_data *data)
{
	init_exec(data);
	data->exec->last_cmd = ft_get_num_cmds(data);
	data->fd->hdoc_index = 0;
	while (data->tokens != NULL)
	{
		reset_params(data);
		resolve_redirections(data);
		if (!data->tokens)
		{
			reset_stdin_stdout(data);
			set_global_exit_code(data);
		}
		else if (data->exec->no_cmd == true || data->tokens->flag == T_WORD)
		{
			exec_cmd(data, data->tokens);
			data->exec->cmd_num++;
		}
		delete_words(data);
		ft_del_first_token(&data);
		close_fds_in_out(data);
	}
	catch_exit_code(data);
	destroy_hdocs(data);
}
