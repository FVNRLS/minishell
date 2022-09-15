/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:29:31 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/15 11:10:14 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

bool	check_sep(t_data *data, char c)
{
	int i;

	i = 0;
	while (data->sep[i] != '\0')
	{
		if (c == data->sep[i])
			return (true);
		i++;
	}
	return (false);
}

bool redir_syntax_error(t_data *data, t_token *token)
{
	bool	is_redir;

	is_redir = check_redir(data, token->flag);
	if (token->flag != T_WORD)
	{
		print_token_error(REDIRECTION_ERROR, token);
		data->lex_error = true;
		if (is_redir == true)
			data->lex_error = true;
		print_token_error(REDIRECTION_ERROR, token);
		return (true);
	}
	return (false);
}

bool	check_redir(t_data *data, int flag)
{
	int i;

	i = 0;
	while (i < NUM_REDIRECTIONS)
	{
		if (flag == data->redir[i])
			return (true);
		i++;
	}
	return (false);
}