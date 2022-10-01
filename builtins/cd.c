/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:42:02 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/26 19:01:13 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	change_pwds(t_data *data)
{
	t_envp	*old;
	t_envp	*pwd;
	char	*old_path;
	char 	*pwd_path;

	old_path = NULL;
	pwd_path = NULL;
	pwd = ft_getenvp(data, "PWD");
	old = ft_getenvp(data, "OLDPWD");
	if (!pwd || !old)
		return ;
	old_path = ft_strdup(pwd->val);
	free(old->val);
	old->val = old_path;

	pwd_path = getcwd(pwd_path, 0);
	free(pwd->val);
	pwd->val = pwd_path;
}

/*
char *dl_equal(char *s) //need later to get right key cause the have an equal
{
	return (NULL);
}
*/

int	cd(t_data *data)
{
	int		ret;
	t_envp	*tmp;

	if (data->exec->last_cmd > 1)
		return (EXIT_SUCCESS);
	tmp = NULL;
	if (!data->builtins->command[1])
	{
		tmp = ft_getenvp(data, "HOME");
		ret = chdir(tmp->val);
		return (ret);
	}
	ret = chdir(data->builtins->command[1]);
	if (ret != 0)
	{
		built_error(PATH_ERROR, data->builtins->command[1]);
		return (EXIT_FAILURE);
	}
	change_pwds(data);
	return (EXIT_SUCCESS);
}
