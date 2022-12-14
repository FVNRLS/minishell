/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 18:32:05 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/13 11:35:07 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	init_lex(t_lex *lex)
{
	lex->i = 0;
	lex->c = 0;
	lex->buf = NULL;
	lex->flag = 0;
	lex->expansion = false;
	lex->single_quote_mode = false;
	lex->double_quote_mode = false;
}

/* 	Analyzes the basic lexical part of the input and creates a linked list of 
	tokens with associated tokens-flags and join-flags.  */
void	lex_input(t_data *data)
{
	t_lex	lex;

	init_lex(&lex);
	data->lex_error = false;
	data->input = ft_strtrim(data->input, SPACE);
	create_tokens(data, &lex);
	free(data->input);
	data->input = NULL;
	if (data->lex_error == true)
		g_exit_code = EXIT_FAILURE;
}
