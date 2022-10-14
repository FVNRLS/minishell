/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:55:19 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/14 20:10:20 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void handle_empty_double_quotes(t_data *data, t_lex *lex)
{
	t_token	*tmp;
	char	*content;
	bool	redirect_found;

	lex->buf = ft_join_char(lex->buf, '\0');
	lex->i++;
	lex->c = data->input[lex->i];
	content = ft_strdup(lex->buf);
	if (!content)
		return ;
	tmp = ft_new_token(content, lex->flag);
	redirect_found = find_redirections(lex);
	if (lex->c != SPACE && redirect_found == false && lex->c != '\0')
		tmp->join = true;
	ft_add_token_back(&data->tokens, tmp);
	free(lex->buf);
	lex->buf = NULL;
}

/* 	Expands the given arguments if needed and/or copies the characters between
	quotes to the buffer. Then creates a token and adds it to the token list. 
*/
static void	expand_double_quotes(t_data *data, t_lex *lex)
{
	bool	redirect_found;

	while (lex->c != DOUBLE_QUOTE)
	{
		if (lex->c == DOLLAR)
			handle_expansion(data, lex);
		else
		{
			lex->buf = ft_join_char(lex->buf, lex->c);
			lex->i++;
			lex->c = data->input[lex->i];
		}
	}
	lex->i++;
	lex->c = data->input[lex->i];
	redirect_found = find_redirections(lex);
	if (lex->c == SPACE || redirect_found == true || lex->c == '\0')
		add_token(data, lex);
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

	lex->double_quote_mode = true;
	quote_not_closed = check_open_quotes(data, lex);
	if (quote_not_closed)
	{
		stop_lexing(data, lex);
		return ;
	}
	lex->flag = T_WORD;
	lex->i++;
	lex->c = data->input[lex->i];
	if (data->input[lex->i] == DOUBLE_QUOTE)
		handle_empty_double_quotes(data, lex);
	else
		expand_double_quotes(data, lex);
	lex->double_quote_mode = false;
}
