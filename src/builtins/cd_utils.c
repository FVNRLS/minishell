/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:39:22 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/10 21:04:41 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	fillempty(t_data *data, char **pwd_path, t_envp **pwd, t_envp **old)
{
    if (!(*pwd) || ft_strlen((*pwd)->val) == 0)
    {
        if ((*pwd))
        {
            free((*pwd)->val);
            (*pwd)->val = ft_strdup(*pwd_path);
        }
        else
        {
            *pwd = ft_new_envp(ft_strdup("PWD"), *pwd_path);
            if (!(*pwd))
                return (EXIT_FAILURE);
            ft_add_envp_back(&data->envp, *pwd);
        }
        
    }
    if (!(*old) || ft_strlen((*old)->val) == 0)
    {
        if ((*old))
        {
            free((*old)->val);
            (*old)->val = ft_strdup((*pwd)->val);
        }
        else
        {
            *old = ft_new_envp(ft_strdup("OLDPWD"), ft_strdup((*pwd)->val));
            if (!(*old) || ft_strlen((*pwd)->val) == 0)
                return (EXIT_FAILURE);
            ft_add_envp_back(&data->envp, *old);
        }
    }
	return (EXIT_SUCCESS);
}

//cd - will change pwd val && OLDPDW dont change even when its emptz
//cd .. will change pwd val && OLDPWD too
int	change_pwds(t_data *data)
{
	t_envp	*old;
	t_envp	*pwd;
	char	*pwd_path;
	char	*new_pwd;
	char	*new_old;

	pwd_path = NULL;
	pwd_path = getcwd(pwd_path, 0);
	pwd = ft_getenvp(data, "PWD");
	old = ft_getenvp(data, "OLDPWD");
    
	if (fillempty(data, &pwd_path, &pwd, &old) == EXIT_FAILURE)
		return (EXIT_FAILURE);
    
	new_old = ft_strdup(pwd->val);
	if (!new_old)
		return (EXIT_FAILURE);
	new_pwd = ft_strdup(pwd_path);
	if (!new_pwd)
		return (EXIT_FAILURE);
	free(pwd->val);
	pwd->val = new_pwd;
	free(old->val);
	old->val = new_old;
    free(pwd_path);
	return (EXIT_SUCCESS);
}

static int	pwd_switch(t_data *data, char *s)
{
	t_envp	*tmp;

	if (s[1] != '\0')
		return (-1);
	tmp = ft_getenvp(data, "OLDPWD");
	if (!tmp || ft_strlen(tmp->val) == 0)
	{
		exec_error(EMPTY_KEY_ERROR, "OLDPWD");
		return (EXIT_FAILURE);
	}
	else
		chdir(tmp->val);
	return (EXIT_SUCCESS);
}

int	home_path(char **s, t_data *data)
{
	char	*path;
	char	*ret;
	int		j;
	int		res;

	res = 0;
	if (s[1][0] == '-')
		return (pwd_switch(data, s[1]));
	if (s[1][0] == '~')
	{
		j = 1;
		path = malloc(sizeof(char) * (ft_strlen(s[1] + 1)));
		if (!path)
			return (EXIT_FAILURE);
		while (s[1][j])
		{
			path[j - 1] = s[1][j];
			j++;
		}
		path[j - 1] = '\0';
		ret = ft_strjoin(ft_strdup(data->builtins->home), path);
	    // printf("%s\n", ret);
		if (!ret)
			return (EXIT_FAILURE);
		free(path);
		res = chdir(ret);    
		free(ret);
	}
	return (res);
}
