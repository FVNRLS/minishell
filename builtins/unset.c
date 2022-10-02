/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:21:26 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/02 15:37:14 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

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
	if (!data->builtins->command[i])
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
