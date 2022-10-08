/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 19:34:04 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/08 10:40:04 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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
}

void	init_shell_env(t_data *data, char **envp)
{
	g_exit_code = 0;
	data->pipe[0] = -1;
	data->pipe[1] = -1;
	data->fd = malloc(sizeof(t_fd));
	if (!data->fd)
		return;
	init_fd(data);
	dup_stdin_and_stdout(data);
	data->exec = malloc(sizeof(t_exec));
	init_exec(data);
	init_flags(data);
	init_data_containers(data);
	data->env = envp;
	init_envp(data, envp);
}