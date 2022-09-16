/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:54:23 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/15 16:48:00 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//TODO: continue with redirects!

void	redirect_in(t_data *data, t_token *token)
{
	data->fd_in = open(token->content, O_RDONLY);
	check_open_error(data, token);
}

void	redirect_from_heredoc(t_data *data, t_token *token)
{
	data->fd_in = open("/tmp/.tmp", O_CREAT | O_RDWR | O_TRUNC, RIGHTS);
	check_open_error(data, token);
}

void	redirect_out(t_data *data, t_token *token)
{
	data->fd_out = open(token->content, O_WRONLY);
	check_open_error(data, token);
}

void	append(t_data *data, t_token *token)
{
	data->fd_out = open(token->content, O_CREAT | O_RDWR | O_TRUNC, RIGHTS);
	check_open_error(data, token);
}

void	resolve_redirections(t_data *data)
{
	t_token	*tmp;
	t_token *del;
	bool	is_redir;

	tmp = data->tokens;
	del = NULL;
	while (tmp->next != NULL && tmp->flag != T_PIPE)
	{
		is_redir = check_redir(data, tmp->flag);
		if (is_redir == true)
		{
			if (tmp->flag == T_REDIRECT_IN)
				redirect_in(data, tmp);
			else if (tmp->flag == T_REDIRECT_OUT)
				redirect_out(data, tmp);
			else if (tmp->flag == T_HEREDOC)
				redirect_from_heredoc(data, tmp);
			else if (tmp->flag == T_APPEND)
				append(data, tmp);
			if (data->parse_error == true)
				return ;
			del = tmp;
			tmp = tmp->next;
			free(del->content);
			del->content = NULL;
			free(del);
			del = NULL;
		}
		else
			tmp = tmp->next;
	}
	printf("fd_in:	%d	fd_out:	%d\n", data->fd_in, data->fd_out);
}
