/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 16:46:39 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/05 18:09:09 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

bool	check_sep(t_data *data, char c)
{
	int	i;

	i = 0;
	while (data->sep[i] != '\0')
	{
		if (c == data->sep[i])
			return (true);
		i++;
	}
	return (false);
}

static void	set_join_flag(t_data *data, t_lex *lex, t_token *token)
{
	char	next_char;

	token->join = false;
	if (data->input[lex->i] == '\0')
		return ;
	next_char = data->input[lex->i + 1];
	if (lex->expansion == true)
	{
		if (lex->c == SINGLE_QUOTE || lex->c == DOUBLE_QUOTE || lex->c == DOLLAR
			|| lex->c == SLASH)
		{
			if (lex->double_quote_mode == true)
			{
				if (next_char == SPACE || next_char == REDIRECT_OUT
					|| next_char == REDIRECT_IN || next_char == PIPE
					|| next_char == '\0')
					return ;
				else
					token->join = true;
			}
			else
				token->join = true;
		}
	}
}

void	add_token(t_data *data, t_lex *lex)
{
	t_token	*tmp;
	char	*content;

	if (!lex->buf)
		return ;
	tmp = NULL;
	content = ft_strdup(lex->buf);
	if (!content)
		return ;
	tmp = ft_new_token(content, lex->flag);
	set_join_flag(data, lex, tmp);
	ft_add_token_back(&data->tokens, tmp);
	free(lex->buf);
	lex->buf = NULL;
}

void	create_tokens(t_data *data, t_lex *lex)
{
	bool	redirect_found;

	while (data->input[lex->i] != '\0' && data->lex_error == false)
	{
		lex->c = data->input[lex->i];
		redirect_found = find_redirections(lex);
		if (redirect_found)
			handle_redirections(data, lex);
		else if (lex->c == SPACE)
			lex->i++;
		else if (lex->c == SINGLE_QUOTE)
			handle_single_quotes(data, lex);
		else if (lex->c == DOLLAR)
			handle_expansion(data, lex);
		else if (lex->c == DOUBLE_QUOTE)
			handle_double_quotes(data, lex);
		else
			handle_words(data, lex);
	}
}
