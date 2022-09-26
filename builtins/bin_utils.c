/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:14:07 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/26 16:33:13 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*make_key(char *s, int *i)
{
	char	*key;

	key = NULL;
	while (s[*i])
	{
		if (s[*i] == '=')
			break ;
		(*i)++;
	}
	key = malloc(sizeof(char) * ((*i) + 1));
	key[(*i) + 1] = '\0';
	*i = 0;
	while (s[(*i)])
	{
		if (s[(*i)] == '=')
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
			printf("declare -x %s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
}
