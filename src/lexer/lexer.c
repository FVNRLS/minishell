/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 18:32:05 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/10 15:29:53 by rmazurit         ###   ########.fr       */
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
	lex->flag = 0;
}

// lexical analyzer program. creates tokens list
void	lex_input(t_data *data)
{
	t_lex	lex;

	init_lex(&lex);
	data->input = ft_strtrim(data->input, DELIMITER);
	if (!data->input)
		exit_with_free(data);
	create_tokens(data, &lex);
	free(data->input);
	data->input = NULL;
}
