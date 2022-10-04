/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:21:26 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/04 14:40:58 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

bool	flag_check(char *s, int mode)
{
	int	i;
	char tmp[2];

	i = 0;
	while (s[i])
	{
		if (s[i] == '-' && s[i + 1] && ft_isprint(s[i + 1]))
		{
			tmp[0] = s[i];
			tmp[1] = s[i + 1];
			if (mode == 1)
				built_error(UNSET_FLAG, tmp);
			else
				built_error(EXPORT_FLAG, tmp);
			return (true);
		}
		i++;
	}
	return (false);
}

static void	dl_node(t_data **data, t_envp *node)
{
	t_envp	*tmp;

	tmp = (*data)->envp;
	while (tmp)
	{
		if (tmp->next && tmp->next->key == node->key)
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

int	unset(t_data *data)
{
	t_envp	*tmp;
	int		i;

	i = 1;
	tmp = NULL;
	if (!data->builtins->command[i] || flag_check(data->builtins->command[i], 1))
		return (EXIT_SUCCESS);
	while (data->builtins->command[i])
	{
		tmp = ft_getenvp(data, data->builtins->command[i]);
		if (tmp != NULL)
			dl_node(&data, tmp);
		i++;
	}
	return (EXIT_SUCCESS);
}
