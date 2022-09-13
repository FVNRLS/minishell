/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:55:19 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/13 19:32:23 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	handle_double_quotes(t_data *data, t_lex *lex)
{
	bool	quote_not_closed;
	bool	redirect_found;

	quote_not_closed = check_open_quotes(data, lex);
	if (quote_not_closed)
		stop_lexing(data, lex);
	lex->flag = T_WORD;
	lex->i++;
	while (data->input[lex->i] != DOUBLE_QUOTE && data->input[lex->i] != '\0')
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
	lex->c = data->input[lex->i];
	redirect_found = find_redirections(lex);
	if (lex->c == SPACE || redirect_found == true || lex->c == '\0')
		add_token(data, lex);
}