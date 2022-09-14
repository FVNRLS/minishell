/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 18:32:05 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/14 19:11:29 by rmazurit         ###   ########.fr       */
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
	merge_joinable_tokens(data);
	merge_redirections(data);
	if (data->lex_error == true)
		return;
	free(data->input);
	data->input = NULL;
}
