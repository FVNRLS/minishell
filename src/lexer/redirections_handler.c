/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:54:52 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/13 11:37:29 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/* Assignment of pipe flag. */
static void	lex_pipe(t_lex *lex)
{
	if (lex->c == '|')
	{
		lex->flag = T_PIPE;
		lex->buf = ft_join_char(lex->buf, lex->c);
		lex->i++;
	}
}

/* Assignment of redirect out and append flags. */
static void	lex_redirect_out(t_data *data, t_lex *lex)
{
	if (lex->c == '>')
	{
		lex->flag = T_REDIRECT_OUT;
		lex->buf = ft_join_char(lex->buf, lex->c);
		lex->i++;
		lex->c = data->input[lex->i];
		if (lex->c == '>')
		{
			lex->flag = T_APPEND;
			lex->buf = ft_join_char(lex->buf, lex->c);
			lex->i++;
		}
	}
}

/* Assignment of redirect in and heredoc flags. */
static void	lex_redirect_in(t_data *data, t_lex *lex)
{
	if (lex->c == '<')
	{
		lex->flag = T_REDIRECT_IN;
		lex->buf = ft_join_char(lex->buf, lex->c);
		lex->i++;
		lex->c = data->input[lex->i];
		if (lex->c == '<')
		{
			lex->flag = T_HEREDOC;
			lex->buf = ft_join_char(lex->buf, lex->c);
			lex->i++;
		}
	}
}

/* 	Decides which flag to assign to the redirection token 
	based on the current character. 
*/
void	handle_redirections(t_data *data, t_lex *lex)
{
	if (lex->c == '<')
		lex_redirect_in(data, lex);
	else if (lex->c == '>')
		lex_redirect_out(data, lex);
	else
		lex_pipe(lex);
	add_token(data, lex);
}

bool	find_redirections(t_lex *lex)
{
	if (lex->c == '<' || lex->c == '>' || lex->c == '|')
		return (true);
	return (false);
}
