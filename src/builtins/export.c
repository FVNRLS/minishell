/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:29:55 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/15 21:45:52 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	*make_val(char *s, int i, int plus)
{
	char	*val;

	val = NULL;
	if (s[i] != '\0' && s[i + 1] != '\0' && !plus)
		val = ft_strdup(s + i + 1);
	else if (s[i] != '\0' && s[i + 1] != '\0' && plus)
	{
		i++;
		if (s[i] != '\0' && s[i + 1] != '\0')
			val = ft_strdup(s + i + 1);
	}
	if (val == NULL)
		val = ft_strdup("");
	return (val);
}

static void	old_key(t_envp *new, char *val, char *key, int plus)
{
	if (new->equal == 0)
	{
		free(key);
		free(val);
		return ;
	}
	free(key);
	if (plus)
	{
		new->val = ft_strjoin(new->val, val);
		free(val);
		return ;
	}
	free(new->val);
	new->val = val;
}

static void	make_envp(char *s, t_data **data, int plus)
{
	char	*key;
	char	*val;
	int		i;
	t_envp	*new;
	t_envp	*list;

	val = NULL;
	list = (*data)->envp;
	i = 0;
	key = make_key(s, &i);
	if (key == NULL)
		return ;
	new = ft_getenvp(*data, key);
	val = make_val(s, i, plus);
	if (new != NULL)
	{
		new->equal = ft_haschar(s, '=');
		old_key(new, val, key, plus);
	}
	else
	{
		new = ft_new_envp(key, val);
		new->equal = ft_haschar(s, '=');
		ft_add_envp_back(&list, new);
	}
}

static void	key_export(t_data **data)
{
	int	i;
	int	plus;

	plus = 0;
	i = 1;
	while ((*data)->exec->cmd[i])
	{
		if (ft_haschar((*data)->exec->cmd[i], '+') && \
		ft_check_plus((*data)->exec->cmd[i]))
			plus = 1;
		make_envp((*data)->exec->cmd[i], data, plus);
		i++;
		plus = 0;
	}
}

/*
export without args will print the whole ENVP list 

exports a new Key and optional its value 
or change an value of an old Key

its saved in ENVP list then
*/
int	export(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	if (!data->exec->cmd[1])
		true_env(data);
	ret = check_keys(data->exec->cmd, EXPORT_ERROR);
	key_export(&data);
	if (ret != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
