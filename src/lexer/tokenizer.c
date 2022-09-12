/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 16:46:39 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/12 17:41:57 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	handle_words(t_data *data, t_lex *lex)
{
	bool redirect_found;

	lex->buf = ft_join_char(lex->buf, lex->c);
	lex->flag = WORD;
	lex->i++;
	lex->c = data->input[lex->i];
	redirect_found = find_redirections(lex);
	if (lex->c == SPACE || redirect_found == true || lex->c == '\0')
		add_token(data, lex);
}

void	add_token(t_data *data, t_lex *lex)
{
	t_token	*tmp;
	char 	*content;

	if (!lex->buf)
		return ;
	tmp = NULL;
	content = ft_strdup(lex->buf);
	if (!content)
		return ;
	tmp = ft_new_token(content, lex->flag);
	if (lex->expansion == true && lex->c != SPACE && lex->c != '\0')
		tmp->join = true;
	else
		tmp->join = false;
	ft_add_token_back(&data->tokens, tmp);
	free(lex->buf);
	lex->buf = NULL;
}

void	create_tokens(t_data *data, t_lex *lex)
{
	bool	redirect_found;

	while (data->input[lex->i] != '\0' && data->lex_error == false)
	{
		lex->c = data->input[lex->i];
		redirect_found = find_redirections(lex);
		if (redirect_found)
			handle_redirections(data, lex);
		else if (lex->c == SPACE)
			lex->i++;
		else if (lex->c == SINGLE_QUOTE)
			handle_single_quotes(data, lex);
		else if (lex->c == DOLLAR)
			handle_expansion(data, lex);
		else
			handle_words(data, lex);
	}
}