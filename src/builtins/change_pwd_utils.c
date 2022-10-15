/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pwd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:24:58 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/15 21:51:12 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	set_pwd(t_data *data, char **pwd_path, t_envp **pwd)
{
	if ((*pwd != NULL))
	{
		if ((*pwd)->val != NULL)
			free((*pwd)->val);
		(*pwd)->val = ft_strdup(*pwd_path);
		if (!(*pwd)->val)
			return (EXIT_FAILURE);
	}
	else
	{
		*pwd = ft_new_envp(ft_strdup("PWD"), ft_strdup(*pwd_path));
		if (!(*pwd))
			return (EXIT_FAILURE);
		ft_add_envp_back(&data->envp, *pwd);
	}
	return (EXIT_SUCCESS);
}

static int	set_oldpwd(t_data *data, t_envp **pwd, t_envp **old)
{
	if ((*old != NULL))
	{
		if ((*old)->val != NULL)
			free((*old)->val);
		(*old)->val = ft_strdup((*pwd)->val);
		if (!(*old)->val)
			return (EXIT_FAILURE);
	}
	else
	{
		*old = ft_new_envp(ft_strdup("OLDPWD"), ft_strdup((*pwd)->val));
		if (!(*old) || ft_strlen((*pwd)->val) == 0)
			return (EXIT_FAILURE);
		ft_add_envp_back(&data->envp, *old);
	}
	return (EXIT_SUCCESS);
}

int	fillempty(t_data *data, char **pwd_path, t_envp **pwd, t_envp **old)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (!(*pwd) || ft_strlen((*pwd)->val) == 0)
		ret = set_pwd(data, pwd_path, pwd);
	if (!(*old) || ft_strlen((*old)->val) == 0)
		ret = set_oldpwd(data, pwd, old);
	return (ret);
}
