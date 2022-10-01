/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:47:27 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/01 12:07:49 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	exec_cmd(t_data *data, t_token *token)
{
	extract_cmd_and_path(data, token);
	if (data->exec_error == true)
		return ;
	if (data->exec->cmd_num < data->exec->last_cmd)
		pipe_transitory_cmd(data);
	else if (data->exec->cmd_num == data->exec->last_cmd)
		pipe_last_cmd(data);
	if (data->builtins->command != NULL)
	{
		ft_cleansplit(data->builtins->command);
		data->builtins->command = NULL;
	}
	free_cmd_and_path(data);
}

void	execute_tokens(t_data *data)
{
	init_exec(data);
	data->exec->last_cmd = ft_get_num_cmds(data);
	while (data->tokens != NULL)
	{
		data->parse_error = false;
		data->exec_error = false;
		data->exec->no_cmd = false;
		data->fd->in = STDIN_FILENO;
		data->fd->out = STDOUT_FILENO;
		resolve_redirections(data);
		merge_words(data);
		if (!data->tokens)
		{
			dup2(data->fd->std_in, STDIN_FILENO);
			dup2(data->fd->std_out, STDOUT_FILENO);
		}
		else if (data->tokens->flag == T_WORD || data->exec->no_cmd == true)
			exec_cmd(data, data->tokens);
		else if (data->tokens->flag == T_PIPE)
			data->exec->cmd_num++;
		ft_del_first_token(&data);
		close_fds_in_out(data);
	}
	destroy_hdocs(data);
}