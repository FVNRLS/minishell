/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:47:27 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/22 13:35:47 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"


int	mod_error(t_data *data)
{
	if (1)
	{
		print_error(7);
		printf("%s\n", data->builtins->command[0]);
		ft_cleansplit(data->builtins->command);
		return (1);
	}
	return (0);	
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
	while (data->tokens && data->exit_minishell != true)
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