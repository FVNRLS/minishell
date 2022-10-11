/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:28:23 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/11 18:02:41 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	check_exit_args(t_data *data, bool *arg_equal_one)
{
	int	i;

	i = 0;
	while (data->builtins->command[i])
		i++;
	if (i > 1)
	{
		if (ft_isnumber(data->builtins->command[1], 0, 0) && i == 2)
			return (ft_atoi(data->builtins->command[1]) % 256);
		else if (ft_isnumber(data->builtins->command[1], 0, 0) && i > 2)
		{
			*arg_equal_one = false;
			print_error(EXIT_ERROR);
			return (EXIT_FAILURE);
		}
		else if (!ft_isnumber(data->builtins->command[1], 0, 0))
		{
			exec_error(EXIT_ARG_ERROR, data->builtins->command[1]);
			return (INVALID_EXIT_ARG);
		}
	}
	return (EXIT_SUCCESS);
}

int	mini_exit(t_data *data)
{
	int		ret;
	bool	arg_equal_one;

	arg_equal_one = true;
	ret = check_exit_args(data, &arg_equal_one);
	if (arg_equal_one == true)
	{
		write(2, "exit\n", 5);
		data->exit_minishell = true;
	}
	return (ret);
}
