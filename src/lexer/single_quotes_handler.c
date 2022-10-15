/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:57:50 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/14 20:06:57 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*
	Iterates the characters in the input and searches for a single/double quote,
	based on the current character lex->c. 
	If there is no appropriate quote, returns true,
	which causes the lexer to stop and the input not to come to execution.
*/
bool	check_open_quotes(t_data *data, t_lex *lex)
{
	int	i;

	i = lex->i + 1;
	if (lex->c == SINGLE_QUOTE)
	{
		while (data->input[i] != '\0')
		{
			if (data->input[i] == SINGLE_QUOTE)
				return (false);
			i++;
		}
	}
	else if (lex->c == DOUBLE_QUOTE)
	{
		while (data->input[i] != '\0')
		{
			if (data->input[i] == DOUBLE_QUOTE)
				return (false);
			i++;
		}
	}
	return (true);
}

void	stop_lexing(t_data *data, t_lex *lex)
{
	data->lex_error = true;
	free(lex->buf);
	lex->buf = NULL;
	if (lex->c == SINGLE_QUOTE)
		print_error(SINGLE_QUOTE_MISSING);
	else if (lex->c == DOUBLE_QUOTE)
		print_error(DOUBLE_QUOTE_MISSING);
}

static void	handle_empty_single_quotes(t_data *data, t_lex *lex)
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

/* 	Copies the characters between quotes to the buffer 
	and adds token to the token list. */
static void	handle_quotes_content(t_data *data, t_lex *lex)
{
	bool	redirect_found;

	while (lex->c != SINGLE_QUOTE)
	{
		lex->buf = ft_join_char(lex->buf, lex->c);
		lex->i++;
		lex->c = data->input[lex->i];
	}
	lex->i++;
	lex->c = data->input[lex->i];
	redirect_found = find_redirections(lex);
	if (lex->c == SPACE || redirect_found == true || lex->c == '\0')
		add_token(data, lex);
}

/*
	Checks if the single quotes are closed. If not - stops the lexing process 
	and sets the lex_error flag to true, which results in the input not being 
	interpreted or executed further. 
	Then evaluates the content between the quotes and creates a
 	word token from it.
*/
void	handle_single_quotes(t_data *data, t_lex *lex)
{
	bool	quote_not_closed;

	lex->single_quote_mode = true;
	quote_not_closed = check_open_quotes(data, lex);
	if (quote_not_closed)
	{
		stop_lexing(data, lex);
		return ;
	}
	lex->flag = T_WORD;
	lex->i++;
	lex->c = data->input[lex->i];
	if (data->input[lex->i] == SINGLE_QUOTE)
		handle_empty_single_quotes(data, lex);
	else
		handle_quotes_content(data, lex);
	lex->single_quote_mode = false;
}
