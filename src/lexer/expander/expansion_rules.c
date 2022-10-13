/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:22:41 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/07 18:33:48 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

/*
 * Here happens the real expansion of the content:
 *
 * Compares the expandable content the DOLLAR sign with the envp. linked list.
 * If envp. with such key exist, the value of the appropriate envp->key becomes
 * is added to the buffer and becomes a token.
 * */
void	try_expansion(t_data *data, t_lex *lex)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp != NULL)
	{
		if (ft_strcmp(lex->buf, tmp->key) == 0)
		{
			free(lex->buf);
			lex->buf = NULL;
			lex->buf = ft_strjoin(lex->buf, tmp->val);
			return ;
		}
		tmp = tmp->next;
	}
	free(lex->buf);
	lex->buf = NULL;
}

/* Expands all expandable content after the DOLLAR sign */
void	expand_parameter(t_data *data, t_lex *lex)
{
	bool	is_sep;

	is_sep = check_sep(data, lex->c);
	while (is_sep == false && lex->c != '\0')
	{
		is_sep = check_sep(data, lex->c);
		if (is_sep == true || lex->c == SLASH)
			break ;
		lex->buf = ft_join_char(lex->buf, lex->c);
		lex->i++;
		lex->c = data->input[lex->i];
	}
	if (lex->buf != NULL)
		try_expansion(data, lex);
}

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
		add_token(data, lex);
	}
	else
	{
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
		add_token(data, lex);
	}
	else
	{
		add_token(data, lex);
		lex->expansion = false;
	}
	lex->i++;
}
