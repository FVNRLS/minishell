/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 18:32:05 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/09 15:28:03 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//TODO : continue!
// add expandable field processing with $

void	init_lex(t_lex *lex)
{
	lex->i = 0;
	lex->c = 0;
	lex->buf = NULL;
}


bool	check_single_quotes(t_data *data, t_lex *lex)
{
	int 	i;
	char	c;

	i = lex->i + 1;
	while (data->input[i] != '\0')
	{
		c = data->input[i];
		if (c == SINGLE_QUOTE)
			return (true);
		i++;
	}
	return (false);
}

void	handle_single_quotes(t_data *data, t_lex *lex)
{
	bool	quote_closed;

	quote_closed = check_single_quotes(data, lex);
	if (quote_closed == false)
	{
		free_all_ressources(data);
		exit(EXIT_FAILURE);
	}
	lex->i++;
	while (data->input[lex->i] != SINGLE_QUOTE && data->input[lex->i] != '\0')
	{
		lex->c = data->input[lex->i];
		lex->buf = ft_join_char(lex->buf, lex->c);
		lex->i++;
	}
	lex->i++;
}

void	create_tokens(t_data *data, t_lex *lex)
{
	lex->c = data->input[lex->i];
	if (data->input[lex->i] == DELIMITER)
		lex->i++;
	else if (lex->c != SINGLE_QUOTE && lex->c != DOUBLE_QUOTE)
	{
		lex->buf = ft_join_char(lex->buf, lex->c);
		lex->i++;
	}
	else if (lex->c == SINGLE_QUOTE)
		handle_single_quotes(data, lex);
}

// lexical analyzer program. creates tokens list
void	lex_input(t_data *data)
{
	t_lex	lex;

	init_lex(&lex);
	while (data->input[lex.i] != '\0')
		create_tokens(data, &lex);
	printf("buffer: %s\n", lex.buf);
	free(data->input);
	data->input = NULL;
}
