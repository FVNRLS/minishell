/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:29:31 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/20 13:20:49 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	check_read_error(t_data *data, t_token *token)
{
	if (data->fd_in < 0 || access(token->content, F_OK < 0)
		|| access(token->content, R_OK) < 0)
	{
		print_token_error(OPEN_ERROR, token);
		data->parse_error = true;
	}
}

void	check_create_error(t_data *data, t_token *token)
{
	if (data->fd_out < 0 || access(token->content, F_OK) < 0)
	{
		perror(token->content);
		data->parse_error = true;
	}
}

void	check_multiple_pipes(t_data *data)
{
	t_token	*tmp;

	tmp = data->tokens;
	if (!tmp)
		return ;
	while (tmp->next != NULL)
	{
		if (tmp->flag == T_PIPE)
		{
			if (tmp->next->flag == T_PIPE)
			{
				print_token_error(PIPE_SYNTAX_ERROR, tmp);
				data->parse_error = true;
				return ;
			}
		}
		tmp = tmp->next;
	}
	if (tmp->flag == T_PIPE)
	{
		print_token_error(PIPE_SYNTAX_ERROR, tmp);
		data->parse_error = true;
		return ;
	}
}

bool 	check_redir_syntax_error(t_data *data, t_token *token)
{
	if (token->next == NULL || token->next->flag != T_WORD)
	{
		print_token_error(REDIR_SYNTAX_ERROR, token);
		data->parse_error = true;
		return (true);
	}
	return (false);
}

bool	check_redir(t_data *data, int flag)
{
	int i;

	i = 0;
	while (i < NUM_REDIRECTIONS)
	{
		if (flag == data->redir[i])
			return (true);
		i++;
	}
	return (false);
}