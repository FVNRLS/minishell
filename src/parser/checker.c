/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:29:31 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/15 11:36:05 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

bool check_redir_syntax_error(t_data *data, t_token *token)
{
	if (token->next == NULL || token->next->flag != T_WORD)
	{
		print_token_error(REDIRECTION_ERROR, token);
		data->parse_error = true;
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