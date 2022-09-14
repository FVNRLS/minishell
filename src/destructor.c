/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:40:53 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/12 15:08:28 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	free_tokens(t_data *data)
{
	t_token	*tmp;
	t_token *head;

	tmp = data->tokens;
	while (tmp != NULL)
	{
		free(tmp->content);
		tmp->content = NULL;
		head = tmp;
		tmp = tmp->next;
		free(head);
		head = NULL;
	}
	data->tokens = NULL;
}

void	free_builtins(t_data *data)
{
	int	i;

	i = 0;
	while (i < NUM_BUILTINS)
	{
		free(data->builtins->names[i]);
		data->builtins->names[i] = NULL;
		i++;
	}
	free(data->builtins);
}

void	free_envp(t_data *data)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp != NULL)
	{
		free(tmp->key);
		tmp->key = NULL;
		free(tmp->val);
		tmp->val = NULL;
		tmp = tmp->next;
	}
	ft_lstclear(&data->envp);
	data->envp = NULL;
}

void	free_all_ressources(t_data *data)
{
	free_builtins(data);
	free_envp(data);
	free_tokens(data);
	free(data->sep);
	data->sep = NULL;
	free(data->redir);
	data->redir = NULL;
}

void	exit_with_free(t_data *data)
{
	free_all_ressources(data);
	exit(EXIT_FAILURE);
}