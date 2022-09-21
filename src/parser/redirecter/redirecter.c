/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:54:23 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/21 13:29:56 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void	redirect_del_token(t_data *data, t_token *token)
{
	if (token->flag == T_REDIRECT_IN)
		redirect_in(data, token);
	else if (token->flag == T_REDIRECT_OUT)
		redirect_out(data, token);
	else if (token->flag == T_HEREDOC)
	{
		redirect_from_heredoc(data, token);
		data->fd->hdoc_index++;
	}
	else if (token->flag == T_APPEND)
		append(data, token);
	free(token->content);
	token->content = NULL;
	free(token);
	token = NULL;
}

//TODO: close unused fd's! - resolve leak on "> 1 > 2 > 3"
void	resolve_redirections(t_data *data)
{
	t_token	*tmp;
	t_token *del;
	t_token *prev;

	tmp = data->tokens;
	if (!tmp)
		return ;
	prev = tmp;
	create_heredoc_files(data);
	data->fd->hdoc_index = 0;
	while (tmp != NULL && tmp->flag != T_PIPE)
	{
		del = tmp;
		if (check_redir(data, del->flag) == true)
		{
			if (data->tokens == del)
				data->tokens = del->next;
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
	printf("fd_in:	%d	fd_out:	%d\n", data->fd->fd_in, data->fd->fd_out);
}
