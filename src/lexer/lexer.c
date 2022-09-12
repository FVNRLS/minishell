/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 18:32:05 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/12 15:49:31 by rmazurit         ###   ########.fr       */
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
	lex->exp_items = NULL;
	lex->prev_content = NULL;
	lex->param = NULL;
	lex->flag = 0;
	lex->expansion = false;
}

// lexical analyzer program. creates tokens list
void	lex_input(t_data *data)
{
	t_lex	lex;

	init_lex(&lex);
	data->lex_error = false;
	data->input = ft_strtrim(data->input, SPACE);
	if (!data->input)
		exit_with_free(data);
	create_tokens(data, &lex);
	free(data->input);
	data->input = NULL;
}
