/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:49:28 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/10 21:09:12 by rmazurit         ###   ########.fr       */
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

void	check_()
{

}

void	expand(t_data *data, t_lex *lex)
{
	char	*param;
	char 	c;

	param = NULL;
	while (data->input[lex->i] != DELIMITER && data->input[lex->i] != '\0')
	{
		c = data->input[lex->i];
		param = ft_join_char(param, c);
		lex->i++;
	}


}

void	handle_expansion(t_data *data, t_lex *lex)
{
	if (data->input[lex->i + 1] == '?')
		expand_last_return(lex);
	else if (data->input[lex->i + 1] == SINGLE_QUOTE)
		lex->i++;
	else if (data->input[lex->i + 1] == '\0')
	{
		lex->buf = ft_join_char(lex->buf, lex->c);
		add_token(data, lex);
	}
	else
		expand(data, lex);
}
