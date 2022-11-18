/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:40:53 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/17 11:58:56 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	destroy_hdocs(t_data *data)
{
	int	i;

	if (data->fd->hdoc == NULL)
		return ;
	i = 0;
	while (data->fd->hdoc[i] != NULL)
	{
		unlink(data->fd->hdoc[i]);
		free(data->fd->hdoc[i]);
		data->fd->hdoc[i] = NULL;
		i++;
	}
	free(data->fd->hdoc);
	data->fd->hdoc = NULL;
}

void	free_tokens(t_data *data)
{
	t_token	*del;

	del = NULL;
	if (data->tokens == NULL)
		return ;
	while (data->tokens != NULL)
	{
		del = data->tokens;
		data->tokens = data->tokens->next;
		free(del->content);
		del->content = NULL;
		free(del);
		del = NULL;
	}
	data->tokens = NULL;
}

void	free_builtins(t_data *data)
{
	int	i;

	i = 0;
	while (i < NUM_BUILTINS && data->builtins->names[i] != NULL)
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

/* frees all initialized arrays, data and linked lists */
void	free_all_ressources(t_data *data)
{
	free(data->builtins->home);
	free_builtins(data);
	free_envp(data);
	free_tokens(data);
	free(data->sep);
	free(data->redir);
	close(data->fd->std_in);
	close(data->fd->std_out);
	free(data->fd);
	free(data->exec);
}
