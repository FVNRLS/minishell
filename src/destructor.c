/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:40:53 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/01 15:50:14 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	free_cmd_and_path(t_data *data)
{
	ft_cleansplit(data->exec->cmd);
	data->exec->cmd = NULL;
	free(data->exec->path);
	data->exec->path = NULL;
}

void 	destroy_hdocs(t_data *data)
{
	int	i;

	if (data->fd->hdoc == NULL)
		return;
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
	t_token *del;

	del = NULL;
	if (!data->tokens)
		return ;
	del = NULL;
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
	free(data->fd);
	close(data->fd->std_in);
	close(data->fd->std_out);
	free(data->exec);
}

void	exit_with_free(t_data *data)
{
	free_all_ressources(data);
	exit(EXIT_FAILURE);
}