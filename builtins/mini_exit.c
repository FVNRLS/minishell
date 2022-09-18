/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:28:23 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/18 14:56:38 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	check_exit_args(t_data *data)
{
	t_token *tmp;

	tmp = data->tokens;
	if (data->builtins->command[1])
	{
		if (data->builtins->command[3])
		{
			print_error(6);
			return (1);
		}
		// here = check if numeric value or not weird behavior exit has
	}
	return (0);
}

int	mini_exit(t_data *data)
{
	//printf("data cmd = %s\n", data->builtins->command[0]);
	/*if (data->builtins->command[1])
	{
		data->exit_minishell = check_exit_arg(data->builtins->command[1]);
	}
	if ((!tmp->next && !data->builtins->command[2]))
		data->exit_minishell = true;*/
	if (!data->tokens->next && !check_exit_args(data))
	{
		write(2, "exit minishell\n", 15);
		data->exit_minishell = true;
	}
	return (EXIT_SUCCESS);
}
