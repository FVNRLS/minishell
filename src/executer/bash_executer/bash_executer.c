/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_executer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:35:16 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/23 18:52:50 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void	execute_with_bash(t_data *data, t_token *token)
{
	char	*cmd;

	cmd = get_cmd(data, token);
//	if (execve(pipex->cmd_path, pipex->cmd, env) < 0)
//		exit_with_error(pipex, EXECVE_ERROR);
}

void	exec_bash_commands(t_data *data)
{
	data->exec_error = false;
	t_token	*tmp;

	resolve_redirections(data);
	if (data->parse_error == true)
		return ;
	tmp = data->tokens;
	if (!tmp)
		return ;
	merge_words(data);
	if (tmp->flag == T_WORD)
		execute_with_bash(data, tmp);



	//printf("fd_in:	%d	fd_out:	%d\n", data->fd->in, data->fd->out);
}