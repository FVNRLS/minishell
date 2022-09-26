/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:47:27 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/26 17:51:56 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void try_exec_builtin(t_data *data, int builtin)
{
	data->builtins->funcs[builtin](data);
	ft_cleansplit(data->builtins->command);
	data->builtins->command = NULL;
}


//TODO: exec builtin via execve if next is pipe - else --> only builtin via array
void	exec_cmd(t_data *data)
{
	t_token	*tmp;
	int		builtin;

	data->exec_error = false;
	init_exec(data);
	data->exec->last_cmd = ft_get_num_cmds(data);
	while (data->tokens != NULL)
	{
		resolve_redirections(data);
		merge_words(data);
		tmp = data->tokens;
		if (!tmp)
			break ;
		if (tmp->flag == T_WORD)
		{
			builtin = ft_get_builtin(data);
			if (builtin >= 0)
				try_exec_builtin(data, builtin);
			else
				exec_bash_cmd(data, tmp);
		}
		ft_del_first_token(&data);
	}
	destroy_hdocs(data);
}