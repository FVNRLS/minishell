/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 19:34:04 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/24 17:23:25 by rmazurit         ###   ########.fr       */
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

static void	init_containers(t_data *data)
{
	data->input = NULL;
	data->redir = NULL;
	data->sep = NULL;
	data->envp = NULL;
	data->tokens = NULL;
}

static void init_redirections(t_data *data)
{
	data->redir = malloc(sizeof(int) * 4);
	if (!data->redir)
		exit(EXIT_FAILURE);
	data->redir[0] = T_REDIRECT_IN;
	data->redir[1] = T_REDIRECT_OUT;
	data->redir[2] = T_HEREDOC;
	data->redir[3] = T_APPEND;

}

void	init_exec(t_data *data)
{
	data->exec->cmd = NULL;
	data->exec->path = NULL;
	data->exec->pipe_used = false;
	data->exec->cmd_num = 0;
}

void	init_fd(t_data *data)
{
	data->fd->hdoc = NULL;
	data->fd->in = STDIN_FILENO;
	data->fd->out = STDOUT_FILENO;
	data->fd->hdoc_index = 0;
	data->fd->hdoc_used = false;
}

static void	init_separators(t_data *data)
{
	data->sep = malloc(sizeof(char) * 8);
	if (!data->sep)
	{
		free(data->redir);
		data->redir = NULL;
		exit(EXIT_FAILURE);
	}
	data->sep[0] = SPACE;
	data->sep[1] = SINGLE_QUOTE;
	data->sep[2] = DOUBLE_QUOTE;
	data->sep[3] = REDIRECT_IN;
	data->sep[4] = REDIRECT_OUT;
	data->sep[5] = PIPE;
	data->sep[6] = DOLLAR;
	data->sep[7] = '\0';
}

//init builtin names and connect them to the builtin functions
static void	init_builtins(t_data *data)
{
	init_builtin_names(data);
	init_builtin_functions(data);
}


void	init_shell_env(t_data *data, char **envp)
{
	data->fd = malloc(sizeof(t_fd));
	data->exec = malloc(sizeof(t_exec));
	init_fd(data);
	init_exec(data);
	init_flags(data);
	init_containers(data);
	init_redirections(data);
	init_separators(data);
	data->env = envp;
	init_envp(data, envp);
	init_builtins(data);
}