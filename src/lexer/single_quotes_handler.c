/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 18:57:50 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/09 18:58:45 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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
	bool	redirect_found;

	quote_closed = check_single_quotes(data, lex);
	if (quote_closed == false)
		exit_with_free(data);
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