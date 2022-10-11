/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 19:34:04 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/11 13:20:29 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	reset_old_pwd(t_data *data)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp != NULL && ft_strcmp(tmp->key, "OLDPWD") == 0)
	{
		free(tmp->val);
		tmp->val = ft_strdup("");
	}
}

static void	init_flags(t_data *data)
{
	data->exit_minishell = false;
	data->lex_error = false;
	data->parse_error = false;
	data->exec_error = false;
}

void	init_exec(t_data *data)
{
	data->exec->cmd = NULL;
	data->exec->path = NULL;
	data->exec->cmd_num = 1;
	data->exec->last_cmd = 0;
	data->pid = 0;
}

void	init_shell_env(t_data *data, char **envp)
{
	data->stop_sig_hdoc = 0;
	g_exit_code = 0;
	data->pipe[0] = -1;
	data->pipe[1] = -1;
	data->fd = malloc(sizeof(t_fd));
	if (!data->fd)
		return ;
	init_fd(data);
	dup_stdin_and_stdout(data);
	data->exec = malloc(sizeof(t_exec));
	init_exec(data);
	init_flags(data);
	init_data_containers(data);
	data->env = envp;
	init_envp(data, envp);
	reset_old_pwd(data);
}
