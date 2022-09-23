/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:29:55 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/23 10:17:28 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/*
prints the envp only if it has (key + val)
if (val = empty) its ignored
*/
int	true_env(t_data *data)
{
	t_envp *tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (tmp->key[0] && tmp->val[0])
			printf("declare -x %s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

/*
add key and its val to the end of envp list
*/
void	add_keyval(char **split, t_data *data) //split[0] = key // split[1] = val
{
	t_envp	*new;
	char	*val;

	if (!split[1])
		val = ft_strdup("");
	else
		val = ft_strdup(split[1]);
	new = ft_getenvp(data, split[0]);
	if (new == NULL)
	{
		new = ft_new_envp(ft_strdup(split[0]), val);
		ft_add_envp_back(&data->envp, new);
	}
	else
	{
		free(new->val);
		new->val = val;
	}
}

/*
add key to the end of envp list and val is empty
*/
void	ft_addkey(char *key, t_data *data)
{
	t_envp *new;

	new = ft_getenvp(data, key);
	if (new == NULL)
	{
		new = ft_new_envp(ft_strdup(key), ft_strdup(""));
		ft_add_envp_back(&data->envp, new);
	}
	else
	{
		free(new->val);
		new->val = ft_strdup("");
	}
}

int	ex_helper(t_data *data, int len)
{
	if (len == 1)
		return (true_env(data));
	else
	{	
		print_error(11);
		printf("»%s«\n", data->builtins->command[1]);
		return (EXIT_FAILURE);
	}
}

/*
handle export command
*/
int	export(t_data *data)
{
	char	**split;
	int		splitlen;
	int		i;

	i = 1;
	splitlen = ft_splitlen(data->builtins->command);
	if (splitlen == 1 || data->builtins->command[i][0] == '=')
		return(ex_helper(data, splitlen));
	while (i < splitlen)
	{
		//printf("cmd = %s\n", data->builtins->command[i]);
		split = ft_split(data->builtins->command[i], '=');
		if (ft_haschar(data->builtins->command[i], '='))
		{
			add_keyval(split, data);
		}
		else
		{
			ft_addkey(data->builtins->command[i], data);
		}
		ft_cleansplit(split);
		i++;
	}
	return (EXIT_SUCCESS);
}
