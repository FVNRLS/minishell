/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:57:50 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/10 19:54:46 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

bool	check_open_quotes(t_data *data, t_lex *lex)
{
	int 	i;
	char	c;

	i = lex->i + 1;
	while (data->input[i] != '\0')
	{
		c = data->input[i];
		if (c == SINGLE_QUOTE)
			return (false);
		i++;
	}
	return (true);
}

void 	stop_lexing(t_data *data, t_lex *lex)
{
	data->lex_error = true;
	free(lex->buf);
	lex->buf = NULL;
	print_error(SINGLE_QUOTE_OPEN);
}

void	handle_single_quotes(t_data *data, t_lex *lex)
{
	bool	quote_not_closed;
	bool	redirect_found;

	quote_not_closed = check_open_quotes(data, lex);
	if (quote_not_closed)
		stop_lexing(data, lex);
	lex->flag = WORD;
	lex->i++;
	while (data->input[lex->i] != SINGLE_QUOTE && data->input[lex->i] != '\0')
	{
		lex->c = data->input[lex->i];
		lex->buf = ft_join_char(lex->buf, lex->c);
		lex->i++;
	}
	lex->i++;
	lex->c = data->input[lex->i];
	redirect_found = find_redirections(lex);
	if (lex->c == DELIMITER || redirect_found == true || lex->c == '\0')
		add_token(data, lex);
}