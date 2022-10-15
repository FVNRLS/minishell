/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:28:23 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/13 13:56:30 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	check_exit_args(t_data *data, bool *arg_equal_one)
{
	int	i;

	i = 0;
	while (data->exec->cmd[i])
		i++;
	if (i > 1)
	{
		if (ft_isnumber(data->exec->cmd[1], 0, 0) && i == 2)
			return (ft_atoi(data->exec->cmd[1]) % 256);
		else if (ft_isnumber(data->exec->cmd[1], 0, 0) && i > 2)
		{
			*arg_equal_one = false;
			print_error(EXIT_ERROR);
			return (EXIT_FAILURE);
		}
		else if (!ft_isnumber(data->exec->cmd[1], 0, 0))
		{
			exec_error(EXIT_ARG_ERROR, data->exec->cmd[1]);
			return (INVALID_EXIT_ARG);
		}
	}
	return (EXIT_SUCCESS);
}

/*
exit minishell
*/
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
