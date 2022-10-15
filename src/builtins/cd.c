/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:42:02 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/15 18:05:42 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*
cd
change directory to Home Path of USER
if it exists in env
*/
int	cd_minus(t_data *data)
{
	int	ret;

	ret = home_path(data->exec->cmd, data);
	if (ret == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ret = change_pwds(data);
	pwd();
	return (ret);
}

/*
cd ~
change directory to Home Path of USER
env list does not mather

cd ~/PATH/PATH2
go to directory if it exists
*/
int	cd_tilde(t_data *data)
{
	int	ret;

	ret = home_path(data->exec->cmd, data);
	if (ret == 0)
		ret = change_pwds(data);
	return (ret);
}

/*
cd /PATH/PATH2
go to directory if it exists
*/
int	cd_path(t_data *data)
{
	int	ret;

	ret = chdir(data->exec->cmd[1]);
	if (ret == 0)
		ret = change_pwds(data);
	return (ret);
}

/*
cd
change directory to Home Path of USER
*/
int	cd_home(t_data *data)
{
	int		ret;
	t_envp	*tmp;

	tmp = ft_getenvp(data, "HOME");
	if (!tmp || ft_strlen(tmp->val) == 0)
	{
		exec_error(EMPTY_KEY_ERROR, "HOME");
		return (EXIT_FAILURE);
	}
	ret = chdir(tmp->val);
	change_pwds(data);
	return (ret);
}

/*
cd
change directory to Home Path of USER
if it exists in env

cd /PATH/PATH2
go to directory if it exists
----------------------------
cd ~
change directory to Home Path of USER
env list does not mather

cd ~/PATH/PATH2
go to directory if it exists
-----------------------------
*/
int	cd(t_data *data)
{
	int		ret;

	if (data->exec->last_cmd > 1)
		return (EXIT_FAILURE);
	if (!data->exec->cmd[1])
		return (cd_home(data));
	else if (data->exec->cmd[1][0] == '-')
		return (cd_minus(data));
	else if (data->exec->cmd[1][0] == '~')
		ret = cd_tilde(data);
	else
		ret = cd_path(data);
	if (ret != 0)
	{
		exec_error(PATH_ERROR, data->exec->cmd[1]);
		return (EXIT_FAILURE);
	}
	return (ret);
}
