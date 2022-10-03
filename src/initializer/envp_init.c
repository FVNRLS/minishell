/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:53:00 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/03 23:05:10 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	*get_value(const char *str)
{
	int		i;
	int		offset;
	int 	len;
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

static void	get_pid(t_data *data)
{
	t_envp 	*tmp;

	tmp = ft_new_envp(ft_strdup("?_PID"), ft_itoa((int)getpid()));
	ft_add_envp_back(&data->envp, tmp);
}

void	init_envp(t_data *data, char **env)
{
	t_envp 	*tmp;
	int 	i;
	char	*key;
	char	*val;

	tmp = NULL;
	i= 0;
	get_pid(data);
	while (env[i] != NULL)
	{
		get_envp(data, env[i], &key, &val);
		tmp = ft_new_envp(key, val);
		if (!tmp)
		{
			free_envp(data);
			exit(EXIT_FAILURE);
		}
		ft_add_envp_back(&data->envp, tmp);
		i++;
	}
}
