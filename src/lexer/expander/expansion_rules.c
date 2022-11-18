/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:22:41 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/14 15:13:44 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

/* Expands return of the last pipe process, based on the global g_exit_code. */
void	expand_last_return(t_data *data, t_lex *lex)
{
	char	*exit_code;
	bool	is_sep;

	exit_code = ft_itoa(g_exit_code);
	lex->buf = ft_strjoin(lex->buf, exit_code);
	free(exit_code);
	exit_code = NULL;
	lex->i++;
	lex->c = data->input[lex->i];
	is_sep = check_sep(data, lex->c);
	while (is_sep == false && lex->c != '\0')
	{
		is_sep = check_sep(data, lex->c);
		if (is_sep == true)
			break ;
		lex->buf = ft_join_char(lex->buf, lex->c);
		lex->i++;
		lex->c = data->input[lex->i];
	}
}

/*
 * In case of multiple DOLLAR signs in a row and SPACE sign
 * creates a token with many DOLLAR sign in content.
 * NO expansion of multiple return values is supported!
 * */
void	handle_multiple_dollars(t_data *data, t_lex *lex)
{
	bool	is_sep;

	while (lex->c == DOLLAR)
	{
		lex->buf = ft_join_char(lex->buf, DOLLAR);
		lex->i++;
		lex->c = data->input[lex->i];
	}
	is_sep = check_sep(data, lex->c);
	if (is_sep == true && lex->c != DOUBLE_QUOTE && lex->c != SINGLE_QUOTE)
	{
		lex->expansion = false;
		if (lex->double_quote_mode == false)
			add_token(data, lex);
	}
	else
	{
		if (lex->double_quote_mode == false)
			add_token(data, lex);
		lex->expansion = false;
	}
}

/*
 * In case of only one DOLLAR and SPACE sign - creates a token with dollar
 * sign in content.
 * */
void	handle_one_dollar(t_data *data, t_lex *lex)
{
	bool	is_sep;

	lex->buf = ft_join_char(lex->buf, DOLLAR);
	is_sep = check_sep(data, lex->c);
	if (is_sep == true && lex->c != DOUBLE_QUOTE && lex->c != SINGLE_QUOTE)
	{
		lex->expansion = false;
		if (lex->double_quote_mode == false)
			add_token(data, lex);
	}
	else
	{
		if (lex->double_quote_mode == false)
			add_token(data, lex);
		lex->expansion = false;
	}
	lex->i++;
}
