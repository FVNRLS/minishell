/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:42:02 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/08 18:52:24 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void	change_pwds(t_data *data)
{
	t_envp	*old;
	t_envp	*pwd;
	char	*old_path;
	char	*pwd_path;

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

static int	pwd_switch(t_data *data, char *s)
{
	t_envp	*tmp;

	if (s[1] != '\0')
		return (-1);
	tmp = ft_getenvp(data, "OLDPWD");
	if (ft_strlen(tmp->val) == 0)
	{
		print_error(OLDPWD_ERROR);
		return (0);
	}
	else
		chdir(tmp->val);
	return (0);
}

static int	home_path(char **s, t_data *data)
{
	char	*path;
	char	*ret;
	t_envp	*tmp;
	int		j;
	int		res;

	if (s[1][0] == '-')
		return (pwd_switch(data, s[1]));
	res = 0;
	j = 1;
	path = malloc(sizeof(char) * (ft_strlen(s[1] + 1)));
	tmp = ft_getenvp(data, "HOME");
	while (s[1][j])
	{
		path[j - 1] = s[1][j];
		j++;
	}
	path[j - 1] = '\0';
	ret = ft_strjoin(ft_strdup(tmp->val), path);
	free(path);
	res = chdir(ret);
	free(ret);
	return (res);
}

int	cd(t_data *data)
{
	int		ret;
	t_envp	*tmp;

	tmp = NULL;
	ret = 0;
	if (!data->builtins->command[1])
	{
		tmp = ft_getenvp(data, "HOME");
		ret = chdir(tmp->val);
	}
	else if (data->builtins->command[1][0] == '~' || \
	data->builtins->command[1][0] == '-')
		ret = home_path(data->builtins->command, data);
	else
		ret = chdir(data->builtins->command[1]);
	if (ret != 0)
	{
		built_error(PATH_ERROR, data->builtins->command[1]);
		return (CMD_NOT_FOUND);
	}
	change_pwds(data);
	return (EXIT_SUCCESS);
}
