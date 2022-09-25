/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:21:26 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/26 00:29:44 by jjesberg         ###   ########.fr       */
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

char	*put_equal(char *s)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(s) + 2));
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i++] = '=';
	new[i] = '\0';
	return (new);
}

int	unset(t_data *data)
{
	t_envp	*tmp;
	char	*find;
	int		i;
	int		j;

	i = 1;
	tmp = NULL;
	if (!data->builtins->command[i])
		return (EXIT_SUCCESS);
	while (data->builtins->command[i])
	{
		j = 0;
		find = put_equal(data->builtins->command[i]);
		tmp = ft_getenvp(data, find);
		if (tmp != NULL)
			dl_node(&data, tmp);
		free(find);
		i++;
	}
	return (EXIT_SUCCESS);
}
