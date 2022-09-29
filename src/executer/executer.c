/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:47:27 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/29 13:22:32 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void try_exec_builtin(t_data *data, int builtin)
{
	data->builtins->funcs[builtin](data);
	ft_cleansplit(data->builtins->command);
	data->builtins->command = NULL;
}

void	exec_cmd(t_data *data)
{
	t_token	*tmp;
	int		builtin;

	init_exec(data);
	data->exec->last_cmd = ft_get_num_cmds(data);
	while (data->tokens != NULL)
	{
		data->exec_error = false;
		resolve_redirections(data);
		merge_words(data);
		tmp = data->tokens;
		if (!tmp)
			break ;
		if (tmp->flag == T_WORD)
		{
			builtin = ft_get_builtin(data);
			if (builtin >= 0 && tmp->next == NULL)
			{
				dup2(data->fd->std_in, STDIN_FILENO);
				try_exec_builtin(data, builtin);
			}
			else
				exec_bash_cmd(data, tmp);
			data->exec->cmd_num++;
		}
		ft_del_first_token(&data);
	}
	destroy_hdocs(data);
}