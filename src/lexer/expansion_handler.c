/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:49:28 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/13 17:33:02 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"


static void	expand_last_return(t_data *data, t_lex *lex)
{
	char	*exit_code;
	bool	is_sep;

	exit_code = ft_itoa(g_exit_code);
	lex->buf = ft_strjoin(lex->buf, exit_code);

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

void	try_expansion(t_data *data, t_lex *lex)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp != NULL)
	{
		if (ft_strcmp(lex->buf, tmp->key) == 0)
		{
			lex->buf = ft_strjoin(lex->buf, tmp->val);
			return ;
		}
		tmp = tmp->next;
	}
	free(lex->buf);
	lex->buf = NULL;
}

void	expand_param(t_data *data, t_lex *lex)
{
	bool	is_sep;

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
	if (lex->buf != NULL)
		try_expansion(data, lex);
}

void	handle_expansion(t_data *data, t_lex *lex)
{
	bool	is_sep;
	lex->expansion = true;
	if (lex->buf != NULL)
		add_token(data, lex);
	lex->i++;
	lex->c = data->input[lex->i];
	is_sep = check_sep(data, lex->c);

	if (lex->c == '?')
		expand_last_return(data, lex);

	else if (is_sep == true || lex->c == '\0')
	{
		if (lex->c != SINGLE_QUOTE && lex->c != DOUBLE_QUOTE)
			lex->buf = ft_join_char(lex->buf, DOLLAR);
	}
	else
		expand_param(data, lex);

	if (lex->buf != NULL)
		add_token(data, lex);
	lex->expansion = false;
}
