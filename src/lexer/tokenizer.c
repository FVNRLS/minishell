/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 16:46:39 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/10 14:24:35 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	handle_words(t_data *data, t_lex *lex)
{
	bool redirect_found;

	lex->buf = ft_join_char(lex->buf, lex->c);
	lex->flag = WORD;
	lex->i++;
	redirect_found = find_redirections(lex);
	if (data->input[lex->i] == DELIMITER || redirect_found)
		add_token(data, lex);
}

void	add_token(t_data *data, t_lex *lex)
{
	t_token	*tmp;
	char	*content;

	tmp = NULL;
	content = ft_strdup(lex->buf);
	if (!content)
		exit(EXIT_FAILURE) ;
	tmp = ft_new_token(content, lex->flag);
	ft_add_token_back(&data->tokens, tmp);
	free(lex->buf);
	lex->buf = NULL;
	lex->i++;
}

void	create_tokens(t_data *data, t_lex *lex)
{
	bool	redirect_found;

	while (data->input[lex->i] != '\0')
	{
		lex->c = data->input[lex->i];
		redirect_found = find_redirections(lex);
		if (redirect_found)
			handle_redirections(data, lex);
		else if (lex->c == DELIMITER)
			lex->i++;
		else if (lex->c == SINGLE_QUOTE)
			handle_single_quotes(data, lex);
		else
			handle_words(data, lex);
	}
	add_token(data, lex);
}