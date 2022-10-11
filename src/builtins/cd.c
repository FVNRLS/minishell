/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:42:02 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/11 12:56:02 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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

int	cd_minus(t_data *data)
{
	int	ret;

	ret = home_path(data->builtins->command, data);
	if (ret == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ret = change_pwds(data);
	return (ret);
}

int	cd_tilde(t_data *data)
{
	int	ret;

	ret = home_path(data->builtins->command, data);
	if (ret == 0)
		ret = change_pwds(data);
	return (ret);
}

int	cd_path(t_data *data)
{
	int	ret;

	ret = chdir(data->builtins->command[1]);
	if (ret == 0)
		ret = change_pwds(data);
	return (ret);
}

int	cd(t_data *data)
{
	int		ret;

	if (data->tokens->next != NULL)
		return (EXIT_FAILURE);
	if (!data->builtins->command[1])
		return (cd_home(data));
	else if (data->builtins->command[1][0] == '-')
		return (cd_minus(data));
	else if (data->builtins->command[1][0] == '~')
		ret = cd_tilde(data);
	else
		ret = cd_path(data);
	if (ret != 0)
	{
		exec_error(PATH_ERROR, data->builtins->command[1]);
		return (EXIT_FAILURE);
	}
	return (ret);
}
