/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:54:23 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/10 15:46:38 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void	redirect_stdin_to_pipe(t_data *data)
{
	close(data->pipe[1]);
	dup2(data->pipe[0], STDIN_FILENO);
	close(data->pipe[0]);
}

static void	redirect_token(t_data *data, t_token *token)
{
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
	if (data->parse_error == true)
		g_exit_code = EXIT_FAILURE;
}

static void	redirect_del_token(t_data *data, t_token *token)
{
	if (data->parse_error == false)
		redirect_token(data, token);
	free(token->content);
	token->content = NULL;
	free(token);
	token = NULL;
}

static void	resolve_redir_after_cmd(t_data *data)
{
	t_token	*prev;
	t_token	*tmp;

	prev = data->tokens;
	tmp = data->tokens->next;
	while (tmp != NULL && tmp->flag != T_PIPE)
	{
		if (check_redir(data, tmp->flag) == true)
		{
			prev->next = tmp->next;
			redirect_del_token(data, tmp);
			tmp = prev->next;
		}
		else
		{
			prev = prev->next;
			tmp = tmp->next;
		}
	}
}

void	resolve_redirections(t_data *data)
{
	t_token	*tmp;

	tmp = data->tokens;
	if (!tmp || tmp->flag == T_PIPE)
		return ;
	while (tmp && check_redir(data, tmp->flag) == true)
	{
		data->tokens = tmp->next;
		redirect_del_token(data, tmp);
		tmp = data->tokens;
	}
	if (tmp == NULL || tmp->flag == T_PIPE)
	{
		data->exec->no_cmd = true;
		return ;
	}
	resolve_redir_after_cmd(data);
}
