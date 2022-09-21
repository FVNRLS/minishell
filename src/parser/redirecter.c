/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:54:23 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/20 17:43:09 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//TODO: continue with redirects!

void	redirect_in(t_data *data, t_token *token)
{
	data->fd_in = open(token->content, O_RDONLY);
	check_read_error(data, token);
}

void	redirect_from_heredoc(t_data *data, t_token *token)
{
	data->fd_in = open("/tmp/.tmp", O_CREAT | O_RDWR | O_TRUNC, RIGHTS);
	check_read_error(data, token);

	//later: unlink "/tmp/.tmp"
}

void	redirect_out(t_data *data, t_token *token)
{
	data->fd_out = open(token->content, O_CREAT | O_RDWR | O_TRUNC, RIGHTS);
	check_create_error(data, token);
}

void	append(t_data *data, t_token *token)
{
	data->fd_out = open(token->content, O_CREAT | O_RDWR | O_APPEND, RIGHTS);
	check_create_error(data, token);
}

void	redirect_del_token(t_data *data, t_token *token)
{
	if (token->flag == T_REDIRECT_IN)
		redirect_in(data, token);
	else if (token->flag == T_REDIRECT_OUT)
		redirect_out(data, token);
	else if (token->flag == T_HEREDOC)
		redirect_from_heredoc(data, token);
	else if (token->flag == T_APPEND)
		append(data, token);
	if (data->parse_error == true)
		return ;
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
	printf("fd_in:	%d	fd_out:	%d\n", data->fd_in, data->fd_out);
}
