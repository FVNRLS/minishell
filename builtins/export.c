/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:29:55 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/19 14:35:24 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*get_key(char *s)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (s[i])
	{
		if (s[i] == '=')
			break ;
		i++;
	}
	if (i == ft_strlen(s))
		return (new);
	else
		new = malloc(sizeof(char) * (i + 2));
	new[i + 1] = '\0';
	while (i >= 0)
	{
		new[i] = s[i];
		i--;
	}
	return (new);
}

char	*get_val(char *s)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (s[i])
	{
		if (s[i] == '=')
			break ;
		i++;
	}
	if (s[i] == '\0' || s[i + 1] == '\0')
		return (NULL);
	i++;
	new = ft_strdup(s + i);
	return (new);
}

void	change_env(char **env, char *key, char *val, int flag)
{
	if (flag == 0)
	{
		printf("create new var, dont work atm\n");
		return ;
	}
	free(*env);
	if (val == NULL)
		val = ft_strdup("");
	env = ft_strjoin(key, val);
	printf("ENV = %s\n", *env);
}

int	export(t_data *data)
{
	t_envp *tmp;
	char *n_key;
	char *n_val;
	int old_env;

	old_env = 0;
	tmp = data->envp;
	printf("cmd = %s\n", data->builtins->command[1]);
	n_key = get_key(data->builtins->command[1]);
	n_val = get_val(data->builtins->command[1]);
	//printf("key = %s\n", n_key);
	//printf("val = %s\n", n_val);
	if (!tmp || !tmp->key)
	{	
		printf("export.c Error empty data"); // just for debug
		return (EXIT_FAILURE);
	}
	while (tmp)
	{
		//change Val of getenv(tmp->key);
		if (ft_strcmp(tmp->key, n_key) == 0)
		{
			old_env = 1;
			change_env(&tmp, n_key, n_val, old_env);
			//printf("key = %s\n", tmp->key);
		}
		tmp = tmp->next;
	}
	if (old_env == 0)
	{
		change_env(&tmp, n_key, n_val, old_env);
	}
	free(n_key);
	free(n_val);
	return (EXIT_SUCCESS);
}
