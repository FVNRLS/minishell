/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:28:23 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/21 19:08:27 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	check_exit_args(t_data *data)
{
	t_token *tmp;
	int i;

	tmp = data->tokens;
	i = 0;
	while (data->builtins->command[i])
		i++;
	if (data->builtins->command[1])
	{
		if (i >= 4)
		{
			print_error(6);
			return (1);
		}
		if (data->builtins->command[1] \
		&& !ft_isnumber(data->builtins->command[1]))
		{
			if (data->builtins->command[2] \
			&& ft_isnumber(data->builtins->command[2]))
				return (0);
			print_error(8);
			return (1);
		}
	}
	return (0);
}

int	mini_exit(t_data *data)
{
	if (!data->tokens->next && !check_exit_args(data)) //if no pipe and right syntax of exit
	{
		write(2, "exit minishell\n", 15);
		data->exit_minishell = true;
	}
	return (EXIT_SUCCESS);
}
