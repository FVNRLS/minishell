/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:29:55 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/28 17:35:05 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	check_new(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i][0] == '=')
			built_error(EXPORT_ERROR, s[i]);
		i++;
	}
	return (0);
}

int	check_string(t_data **data, int *i)
{
	char	*s;

	s = (*data)->tokens->content;
	if (ft_strlen(s) == 6)
		return (EXIT_FAILURE);
	while (ft_isprint(s[*i]))
		(*i)++;
	(*i)++;
	ft_cleansplit((*data)->builtins->command);
	(*data)->builtins->command = ft_split(s + (*i), ' ');
	if (check_new((*data)->builtins->command))
	{
		i = 0;
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

void	make_envp(char *s, t_data **data)
{
	char 	*key;
	char	*val;
	int		i;
	t_envp	*new;
	t_envp *list;

	list = (*data)->envp;
	i = 0;
	key = make_key(s, &i);
	new = ft_getenvp(*data, key);
	val = ft_strdup(s + i + 1);
	if (val == NULL)
		val = ft_strdup("");
	if (new != NULL)
	{
		if (ft_strlen(val) != 0)
		{
			free(new->val);
			new->val = val;
		}
		else
			free(val);
	}
	else
	{
		new = ft_new_envp(key, val);
		ft_add_envp_back(&list, new);
	}
}

void	key_export(t_data **data)
{
	int	i;

	i = 0;
	while ((*data)->builtins->command[i])
	{
		if ((*data)->builtins->command[i][0] == '=')
			i++;
		else if ((*data)->builtins->command[i])
		{
			make_envp((*data)->builtins->command[i], data);
			i++;
		}
	}
	
}

int	export(t_data *data)
{
	int	i;

	i = 0;
	if (check_string(&data, &i))
		true_env(data);
	if (i == 0)
		return (EXIT_FAILURE);
	key_export(&data);
	return (EXIT_SUCCESS);
}
