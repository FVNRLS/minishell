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

static void	init_flags(t_data *data)
{
	data->exit_minishell = false;
	data->error = false;
	data->status = 0;
}

static void	init_containers(t_data *data)
{
	data->input = NULL;
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
	init_flags(data);
	init_containers(data);
	init_envp(data, envp);
	init_builtins(data);
}