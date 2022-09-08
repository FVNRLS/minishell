/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 18:32:05 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/08 19:57:36 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"


void	create_token(t_data *data, int start, int end)
{


}

int	find_closing_quote(t_data *data, int quote_start)
{
	int 	i;
	char	c;

	i = quote_start + 1;
	while (data->input[i] != '\0')
	{
		c = data->input[i];
		if (c == SINGLE_QUOTE)
			return (i);
	}
	return (0);
}

//TODO : continue!
// lexical analyzer program. creates tokens list
void	lex_input(t_data *data)
{
	int 	i;
	int 	quote_end;
	char 	c;
	char 	*buf;
	bool	quotes_closed;

	buf = NULL;
	i = 0;
	while (data->input[i] != '\0')
	{
		quotes_closed = false;
		c = data->input[i];
		if (c == DELIMITER)
			i++;
		else if (c == SINGLE_QUOTE)
		{
			quote_end = find_closing_quote(data, i);
			if (quote_end == 0)
			{
				free_all_ressources(data);
				exit(EXIT_FAILURE);
			}
			create_token(data, i, quote_end);
			i = quote_end;
		}

	}
	free(data->input);
	data->input = NULL;
}
