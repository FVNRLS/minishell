/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:47:27 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/24 17:53:45 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//TODO:
//export need rework
//some error messages are wrong
//and signals not done yet

int	mod_error(t_data *data)
{
	built_error(CMD_ERROR, data->builtins->command[0]);
	ft_cleansplit(data->builtins->command);
	data->exec_error = true;
	return (1);
}

/*
cmd exec
*/
void	exec_commands(t_data *data)
{
	t_token *tmp;
	int		mod;

	data->exec_error = false;
	tmp = (t_token*)data->tokens;
	while (data->tokens && !data->exit_minishell && !data->exec_error)
	{
		mod = ft_isbuiltin(data);
		//printf("mod = %i\n", mod);
		if (mod == -1 && mod_error(data))
			break ;
		if (mod != -1)
		{
			data->builtins->funcs[mod - 1](data);
			data->tokens = data->tokens->next;
		}
		ft_cleansplit(data->builtins->command);
	}
}