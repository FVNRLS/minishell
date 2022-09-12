/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 19:34:04 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/08 13:41:24 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	init_separators(t_data *data)
{
	data->sep = malloc(sizeof(char) * 10);
	if (!data->sep)
		exit(EXIT_FAILURE);
	data->sep[0] = SPACE;
	data->sep[1] = SINGLE_QUOTE;
	data->sep[2] = DOUBLE_QUOTE;
	data->sep[3] = WORD;
	data->sep[4] = REDIRECT_IN;
	data->sep[5] = REDIRECT_OUT;
	data->sep[6] = APPEND_IN;
	data->sep[7] = HEREDOC;
	data->sep[8] = PIPE;
	data->sep[9] = '\0';
}

static void	init_flags(t_data *data)
{
	data->exit_minishell = false;
	data->lex_error = false;
	data->status = 0;
}

static void	init_containers(t_data *data)
{
	data->input = NULL;
	data->envp = NULL;
	data->tokens = NULL;
}

//init builtin names and connect them to the builtin functions
static void	init_builtins(t_data *data)
{
	init_builtin_names(data);
	init_builtin_functions(data);
}


void	init_shell_env(t_data *data, char **envp)
{
	init_separators(data);
	init_flags(data);
	init_containers(data);
	init_envp(data, envp);
	init_builtins(data);
}