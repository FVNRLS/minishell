/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:28:23 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/11 16:43:12 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	check_exit_args(t_data *data, bool *arg_equal_one)
{
	int	i;
	int num;

	i = 0;
	while (data->builtins->command[i])
		i++;
	if (i > 1)
	{
		if (ft_isnumber(data->builtins->command[1], 0, 0) && i == 2)
		{
			num = ft_atoi(data->builtins->command[1]);
			*arg_equal_one = true;
			return (num % 256);
		}
		else if (ft_isnumber(data->builtins->command[1], 0, 0) && i > 2)
		{
			print_error(EXIT_ERROR);
			return (EXIT_FAILURE);
		}
		else if (!ft_isnumber(data->builtins->command[1], 0, 0))
		{
			*arg_equal_one = true;
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

	arg_equal_one = false;
	ret = check_exit_args(data, &arg_equal_one);
	if (arg_equal_one == true)
	{
		write(2, "exit\n", 5);
		data->exit_minishell = true;
	}
	return (ret);
}
