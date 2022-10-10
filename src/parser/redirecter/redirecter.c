/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:54:23 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/09 15:25:09 by rmazurit         ###   ########.fr       */
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
	if (data->tokens == token)
		data->tokens = token->next;
	if (data->parse_error == false)
		redirect_token(data, token);
	free(token->content);
	token->content = NULL;
	free(token);
	token = NULL;
}

static void	set_no_cmd_flag(t_data *data)
{
	if (data->exec->words == 0)
		data->exec->no_cmd = true;
}

void	resolve_redirections(t_data *data)
{
	t_token	*tmp;
	t_token	*del;
	t_token	*prev;

	tmp = data->tokens;
	if (!tmp || tmp->flag == T_PIPE)
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
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
			data->exec->words++;
		}
	}
	set_no_cmd_flag(data);
}
