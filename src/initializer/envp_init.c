/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:53:00 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/11 10:29:23 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	*get_value(const char *str)
{
	int		i;
	int		offset;
	int		len;
	char	*val;

	val = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			offset = i + 1;
		i++;
	}
	len = i - offset;
	val = ft_calloc(len + 1, sizeof(char));
	if (!val)
		return (NULL);
	i = 0;
	while (str[offset] != '\0')
		val[i++] = str[offset++];
	val[i] = '\0';
	return (val);
}

static char	*get_key(const char *str)
{
	int		i;
	char	*key;

	key = NULL;
	i = 0;
	while (str[i] != '=')
		i++;
	key = ft_calloc(i + 1, sizeof(char));
	if (!key)
		return (NULL);
	i = 0;
	while (str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

static void	get_envp(t_data *data, char *str, char **key, char **val)
{
	*key = get_key(str);
	if (!*key)
	{
		free_envp(data);
		exit(EXIT_FAILURE);
	}
	*val = get_value(str);
	if (!*val)
	{
		free(*key);
		free_envp(data);
		exit(EXIT_FAILURE);
	}
}

void	init_envp(t_data *data, char **env)
{
	t_envp	*tmp;
	int		i;
	char	*key;
	char	*val;

	tmp = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		get_envp(data, env[i], &key, &val);
		tmp = ft_new_envp(key, val);
		if (!tmp)
		{
			free_envp(data);
			exit(EXIT_FAILURE);
		}
		if (ft_strcmp(tmp->key, "HOME") == 0)
			data->builtins->home = ft_strdup(tmp->val);
		tmp->equal = true;
		ft_add_envp_back(&data->envp, tmp);
		i++;
	}
}
