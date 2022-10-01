/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:21:26 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/01 14:01:55 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	dl_node(t_data **data, t_envp *node)
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

	if (data->exec->last_cmd > 1)
		return (EXIT_SUCCESS);
	i = 1;
	tmp = NULL;
	if (!data->builtins->command[i])
		return (EXIT_FAILURE);
	while (data->builtins->command[i])
	{
		tmp = ft_getenvp(data, data->builtins->command[i]);
		if (tmp != NULL)
			dl_node(&data, tmp);
		else
			built_error(UNSET_ERROR, data->builtins->command[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
