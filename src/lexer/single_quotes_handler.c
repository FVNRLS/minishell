/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:57:50 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/10 11:54:11 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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

static void	handle_quotes_content(t_data *data, t_lex *lex)
{
	bool	redirect_found;

	while (data->input[lex->i] != SINGLE_QUOTE && data->input[lex->i] != '\0')
	{
		lex->c = data->input[lex->i];
		lex->buf = ft_join_char(lex->buf, lex->c);
		lex->i++;
	}
	lex->i++;
	lex->c = data->input[lex->i];
	redirect_found = find_redirections(lex);
	if (lex->c == SPACE || redirect_found == true || lex->c == '\0')
		add_token(data, lex);
}

static void	handle_empty_quotes(t_data *data, t_lex *lex)
{
	t_token	*tmp;
	char	*content;

	tmp = data->tokens;
	if (!tmp)
		return ;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->join == false)
	{
		lex->i++;
		lex->c = data->input[lex->i];
		lex->buf = ft_join_char(lex->buf, SPACE);
		content = ft_strdup(lex->buf);
		if (!content)
			return ;
		tmp = ft_new_token(content, lex->flag);
		tmp->join = true;
		ft_add_token_back(&data->tokens, tmp);
		free(lex->buf);
		lex->buf = NULL;
	}
	lex->i++;
	lex->c = data->input[lex->i];
}

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
	if (data->input[lex->i] == SINGLE_QUOTE)
		handle_empty_quotes(data, lex);
	else
		handle_quotes_content(data, lex);
	lex->single_quote_mode = false;
}
