/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:14:07 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/26 00:27:18 by jjesberg         ###   ########.fr       */
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
	key = malloc(sizeof(char) * ((*i) + 2));
	key[(*i) + 1] = '\0';
	*i = 0;
	while (s[(*i)])
	{
		key[(*i)] = s[(*i)];
		if (s[(*i)] == '=')
			break ;
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
		if (tmp->key[0] && tmp->val[0])
			printf("declare -x %s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
}
