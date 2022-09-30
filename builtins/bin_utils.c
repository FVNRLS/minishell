/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:14:07 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/30 12:49:15 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*make_key(char *s, int *i)
{
	char	*key;

	key = NULL;
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
		if (s[(*i)] == '='|| s[*i] == '+')
			break ;
		key[(*i)] = s[(*i)];
		(*i)++;
	}
	return (key);
}

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
			else
				printf("declare -x %s\n", tmp->key);
		}
		tmp = tmp->next;
	}
}
