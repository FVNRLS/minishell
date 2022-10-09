/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:49:28 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/09 10:44:59 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void	handle_expandable_parameter(t_data *data, t_lex *lex)
{
	bool	is_sep;

	lex->i++;
	lex->c = data->input[lex->i];
	is_sep = check_sep(data, lex->c);
	if (lex->c == '?')
		expand_last_return(data, lex);
	else if (is_sep == true || lex->c == '\0')
	{
		if (lex->c == SINGLE_QUOTE || lex->c == DOUBLE_QUOTE)
		{
			if (lex->single_quote_mode == true
				|| lex->double_quote_mode == true)
				lex->buf = ft_join_char(lex->buf, DOLLAR);
		}
	}
	else
		expand_parameter(data, lex);
	if (lex->buf != NULL)
		add_token(data, lex);
	lex->expansion = false;
}

void	handle_expansion(t_data *data, t_lex *lex)
{
	lex->expansion = true;
	if (lex->buf != NULL)
		add_token(data, lex);
	if (data->input[lex->i + 1] == SPACE || data->input[lex->i + 1] == '\0')
	{
		handle_one_dollar(data, lex);
		return ;
	}
	else if (data->input[lex->i + 1] == DOLLAR)
	{
		handle_multiple_dollars(data, lex);
		return ;
	}
	else
		handle_expandable_parameter(data, lex);
}
