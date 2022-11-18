/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:54:23 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/13 13:27:07 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

/* closes unused pipes and redirects the command input in to the next pipe */
void	redirect_stdin_to_pipe(t_data *data)
{
	close(data->pipe[1]);
	dup2(data->pipe[0], STDIN_FILENO);
	close(data->pipe[0]);
}

/* decides how to redirct a token based on token flag */
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

/* applies redirection rules on the token and deletes it from the tokens list */
static void	redirect_del_token(t_data *data, t_token *token)
{
	if (data->parse_error == false)
		redirect_token(data, token);
	free(token->content);
	token->content = NULL;
	free(token);
	token = NULL;
}

/* helper funciton for the redirection process */
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

/* 	
	checks if a current token is a redirection and resolves it by
	assigning the fd number of standard input and output to fd->in and fd->out.
	There can be only one stdin and stdout in the end. 
	Otherwise, all previous unused (opened) fd's will be closed.
	The function is always called for each command separately (between pipes).
	If there was no T_WORD token until the next pipe, the data->exec->no_cmd 
	is set to true.
*/
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
