/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:55:19 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/13 11:53:41 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/* 	Expands the given arguments if needed and/or copies the characters between
	quotes to the buffer. Then creates a token and adds it to the token list. 
*/
static void	expand_double_quotes(t_data *data, t_lex *lex)
{
	lex->flag = T_WORD;
	lex->i++;
	while (data->input[lex->i] != DOUBLE_QUOTE)
	{
		lex->c = data->input[lex->i];
		if (lex->c == DOLLAR)
			handle_expansion(data, lex);
		else
		{
			lex->buf = ft_join_char(lex->buf, lex->c);
			lex->i++;
		}
	}
	lex->i++;
}

/*
	Checks if the double quotes are closed. If not - stops the lexing process 
	and sets the lex_error flag to true, which results in the input not being 
	interpreted or executed further. 
	Then evaluates the content between the quotes, expands the expandable
	arguments if needed and creates a word token from it.
*/
void	handle_double_quotes(t_data *data, t_lex *lex)
{
	bool	quote_not_closed;
	bool	redirect_found;

	lex->double_quote_mode = true;
	quote_not_closed = check_open_quotes(data, lex);
	if (quote_not_closed)
	{
		stop_lexing(data, lex);
		return ;
	}
	expand_double_quotes(data, lex);
	lex->c = data->input[lex->i];
	redirect_found = find_redirections(lex);
	if (lex->c == SPACE || redirect_found == true || lex->c == '\0')
		add_token(data, lex);
	lex->double_quote_mode = false;
}
