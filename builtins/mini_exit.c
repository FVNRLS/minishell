/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:28:23 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/26 16:07:35 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	check_exit_args(t_data *data)
{
	t_token	*tmp;
	int		i;

	tmp = data->tokens;
	i = 0;
	while (data->builtins->command[i])
		i++;
	if (data->builtins->command[1])
	{
		if (i >= 3)
		{
			print_error(EXIT_ERROR);
			return (1);
		}
		if (data->builtins->command[1] \
		&& !ft_isnumber(data->builtins->command[1]))
		{
			if (data->builtins->command[2] \
			&& ft_isnumber(data->builtins->command[2]))
				return (0);
			built_error(EXIT_ARG_ERROR, data->builtins->command[1]);
		}
	}
	return (0);
}

int	mini_exit(t_data *data)
{
	if (!data->tokens->next && !check_exit_args(data))
	{
		write(2, "exit minishell\n", 15);
		data->exit_minishell = true;
	}
	return (EXIT_SUCCESS);
}
