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


void	create_tokens(t_data *data)
{


}

bool	check_quotes(t_data *data)
{
	int 	single_quotes;
	int 	double_quotes;
	int 	i;
	char 	c;

	single_quotes = 0;
	double_quotes = 0;
	i = 0;
	while (data->input[i] != '\0')
	{
		c = data->input[i];
		if (ft_strcmp(&c, "\'") == 0)
			single_quotes++;
		if (ft_strcmp(&c, "\"") == 0)
			double_quotes++;
	}
	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
		return (false);
	return (true);
}

//TODO : continue!
// lexical analyzer program. creates tokens list
void	lex_input(t_data *data)
{
	int 	i;
	char 	c;
	bool	all_quotes_closed;

	all_quotes_closed = check_quotes(data);
	if (all_quotes_closed == true)
	{
		i = 0;
		while (data->input[i] != '\0')
		{
			c = data->input[i];
			if (ft_strcmp(&c, DELIMITER) == 0)
				i++;
		}
	}
	else
		exit(EXIT_FAILURE);

	free(data->input);
	data->input = NULL;
}



