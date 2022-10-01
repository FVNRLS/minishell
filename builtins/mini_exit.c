/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:28:23 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/01 13:23:16 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	check_exit_args(t_data *data)
{
	int		i;

	i = 0;
	while (data->builtins->command[i])
		i++;
	if (i > 1)
	{
		if (ft_isnumber(data->builtins->command[1], 0, 0) && i == 2)
		{
			return (1);
		}
		else if (ft_isnumber(data->builtins->command[1], 0, 0) && i > 2)
		{
			print_error(EXIT_ERROR);
			return (0);
		}
		else if (!ft_isnumber(data->builtins->command[1], 0, 0))
			return (built_error(EXIT_ARG_ERROR, data->builtins->command[1]));
	}
	return (1);
}


int	mini_exit(t_data *data)
{
	if (data->exec->last_cmd == 1)
	{
		write(1, "exit\n", 5);
		data->exit_minishell = true;
	}
	check_exit_args(data);
	return (EXIT_SUCCESS);
}
