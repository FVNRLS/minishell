/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:49:28 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/11 11:53:53 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"


//TODO: continue here, check $? expansion
void	expand_last_return(t_lex *lex)
{
	char *exit_code;

	exit_code = ft_itoa(g_exit_code);
	lex->buf = ft_strjoin(lex->buf, exit_code);
}

bool	check_envp(t_data *data, t_lex *lex)
{

}

bool	expand_previous_part(t_data *data, t_lex *lex)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp != NULL)
	{
		if (ft_strcmp(lex->buf, data->envp->key) == 0)
		{
			free(lex->buf);
			lex->buf = NULL;
			lex->buf = ft_strjoin(lex->buf, data->envp->val);
		}
		tmp = tmp->next;

	}

}

void	expand_expression(t_data *data, t_lex *lex)
{
	lex->c = data->input[lex->i];
	while (lex->c == DELIMITER && lex->c == '\0')
	{
		lex->c = data->input[lex->i];
		if (lex->c == '?' && data->input[lex->i - 1] == EXPANSION)
		{
			expand_last_return(lex);
			lex->i++;
		}
		else if (lex->c == EXPANSION)
			expand_previous_part(data, lex);
		else
		{
			lex->buf = ft_join_char(lex->buf, lex->c);
			lex->i++;
		}
	}
	add_token(data, lex);
	lex->i++;


}

void	handle_expansion(t_data *data, t_lex *lex)
{
	char c;

	c = data->input[lex->i + 1];

	if (c == DELIMITER || c == '\0')
	{
		lex->buf = ft_join_char(lex->buf, lex->c);
		add_token(data, lex);
	}
	else if (c == SINGLE_QUOTE)
		lex->i++;
	else
	{
		lex->i++;
		expand_expression(data, lex);
	}
}
