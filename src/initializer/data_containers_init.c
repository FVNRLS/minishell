/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_containers_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:35:54 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/08 10:36:12 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//init builtin names and connect them to the builtin functions
static void	init_builtins(t_data *data)
{
	init_builtin_names(data);
	init_builtin_functions(data);
	data->builtins->command = NULL;
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

void	init_data_containers(t_data *data)
{
	data->input = NULL;
	data->redir = NULL;
	data->sep = NULL;
	data->envp = NULL;
	data->tokens = NULL;
	init_redirections(data);
	init_separators(data);
	init_builtins(data);
}