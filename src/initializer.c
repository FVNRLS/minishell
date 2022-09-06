/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 19:34:04 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/06 19:34:46 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void	init_flags(t_data *data)
{
	data->exit_minishell = false;
	data->status = 0;
}

static void	init_pointers(t_data *data)
{

}

//init builtin names and functions
static void	init_builtins(t_data *data)
{

}

static void	init_envp(t_data *data)
{

}


void	init(t_data *data)
{
	init_flags(data);
	init_pointers(data);
	init_builtins(data);
	init_envp(data);
}