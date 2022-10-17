/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:12:51 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/13 13:50:32 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*
prints ENVP list completly
*/
void	true_env(t_data *data)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (tmp->key[0])
		{
			if (ft_strlen(tmp->val) != 0)
				printf("declare -x %s=\"%s\"\n", tmp->key, tmp->val);
			else if (tmp->equal == false)
				printf("declare -x %s\n", tmp->key);
			else if (tmp->equal == true)
				printf("declare -x %s=\"\"\n", tmp->key);
		}
		tmp = tmp->next;
	}
}

static int	true_key(char *s)
{
	int	i;

	i = 1;
	if (!s || ft_strlen(s) < 1)
		return (0);
	if (s[0] != '_' && !ft_isalpha(s[0]))
		return (0);
	while (s[i])
	{
		if ((s[i] == '=' && i != 0) || (s[i] == '+' \
		&& s[i + 1] && s[i + 1] == '=' && i != 0))
			return (1);
		else if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]) \
		&& s[i] != '_' && i != 0)
			return (0);
		i++;
	}
	return (1);
}

char	*make_key(char *s, int *i)
{
	char	*key;

	key = NULL;
	if (!true_key(s))
		return (key);
	while (s[*i])
	{
		if (s[*i] == '=' || s[*i] == '+')
			break ;
		(*i)++;
	}
	key = malloc(sizeof(char) * ((*i) + 1));
	key[(*i)] = '\0';
	*i = 0;
	while (s[(*i)])
	{
		if (s[(*i)] == '=' || s[*i] == '+')
			break ;
		key[(*i)] = s[(*i)];
		(*i)++;
	}
	return (key);
}
