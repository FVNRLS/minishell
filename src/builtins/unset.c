/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:21:26 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/09 19:14:13 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	dl_node(t_data **data, t_envp *node)
{
	t_envp	*tmp;

	tmp = (*data)->envp;
	if (ft_strcmp(tmp->key, node->key) == 0)
	{
		(*data)->envp = tmp->next;
		free(node->val);
		free(node->key);
		free(node);
		return ;
	}
	while (tmp->next)
	{
		if ((ft_strcmp(tmp->next->key, node->key) == 0))
		{
			tmp->next = tmp->next->next;
			free(node->key);
			free(node->val);
			free(node);
			break ;
		}
		tmp = tmp->next;
	}
}

static void	check_keys_help(char **s, int *i, int *j)
{
	while (s[(*i)] != NULL && s[(*i)][(*j)] && s[(*i)][(*j) + 1])
	{
		(*j)++;
		if (s[*i][*j] == '=' || (s[*i][*j] == '+' \
		&& *j < (int)ft_strlen(s[*i]) && s[*i][(*j) + 1] == '='))
			break ;
		if (!ft_isalpha(s[*i][*j]) && !ft_isdigit((int)s[*i][*j]) \
		&& s[*i][*j] != '_')
			break ;
	}
}

void	check_keys(char **s, int mode)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i] && i < ft_splitlen(s))
	{
		j = 0;
		if (!ft_isalpha(s[i][j]) && s[i][j] != '_')
			exec_error(mode, s[i]);
		else
			check_keys_help(s, &i, &j);
		i++;
	}
}

static int	check_unset(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (1);
	while (s[i])
	{
		if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]) && s[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	unset(t_data *data)
{
	t_envp	*tmp;
	int		i;

	i = 1;
	if (!data->builtins->command[i])
		return (EXIT_FAILURE);
//	check_keys(data->builtins->command, UNSET_ERROR); //del error print
	while (data->builtins->command[i])
	{
		tmp = NULL;
		if (check_unset(data->builtins->command[i]))
			exec_error(UNSET_ERROR, data->builtins->command[i]);
		else
			tmp = ft_getenvp(data, data->builtins->command[i]);
		if (tmp != NULL)
			dl_node(&data, tmp);
		i++;
	}
	return (EXIT_SUCCESS);
}
