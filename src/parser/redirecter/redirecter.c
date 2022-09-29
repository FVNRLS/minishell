/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:54:23 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/25 12:19:28 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void	redirect_del_token(t_data *data, t_token *token)
{
	if (data->tokens == token)
		data->tokens = token->next;
	if (token->flag == T_REDIRECT_IN)
		redirect_in(data, token);
	else if (token->flag == T_HEREDOC)
	{
		redirect_from_hdoc(data);
		data->fd->hdoc_index++;
	}
	else if (token->flag == T_REDIRECT_OUT)
		redirect_out(data, token);
	else if (token->flag == T_APPEND)
		append(data, token);
	free(token->content);
	token->content = NULL;
	free(token);
	token = NULL;
}

void	resolve_redirections(t_data *data)
{
	t_token	*tmp;
	t_token *del;
	t_token *prev;

	data->fd->hdoc_index = 0;
	tmp = data->tokens;
	if (!tmp)
		return ;
	prev = tmp;
	while (tmp != NULL && tmp->flag != T_PIPE)
	{
		del = tmp;
		if (check_redir(data, del->flag) == true)
		{
			prev->next = del->next;
			tmp = del->next;
			redirect_del_token(data, del);
			if (data->parse_error == true)
				return ;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}
