/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:28:23 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/08 15:18:11 by jjesberg         ###   ########.fr       */
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
			return (ft_atoi(data->builtins->command[1]) % 256);
		else if (ft_isnumber(data->builtins->command[1], 0, 0) && i > 2)
		{
			print_error(EXIT_ERROR);
			return (EXIT_ERROR);
		}
		else if (!ft_isnumber(data->builtins->command[1], 0, 0))
		{
			built_error(EXIT_ARG_ERROR, data->builtins->command[1]);
			return (INVALID_EXIT_ARG);
		}
	}
	return (EXIT_SUCCESS);
}

int	mini_exit(t_data *data)
{
	int	ret;

	ret = check_exit_args(data);
	if (ret != EXIT_ERROR)
	{
		write(2, "exit\n", 5);
		data->exit_minishell = true;
	}
	return (ret);
}
