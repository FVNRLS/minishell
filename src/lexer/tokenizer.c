/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 16:46:39 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/13 17:46:58 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	join_tokens(t_data *data)
{
	t_token	*tmp;
	t_token	*del;

	tmp = data->tokens;
	if (!tmp)
		return ;
	del = NULL;
	while (tmp->next != NULL)
	{
		if (tmp->join == true)
		{
			del = tmp->next;
			tmp->content = ft_strjoin(tmp->content, del->content);
			tmp->join = del->join;
			tmp->next = del->next;
			free(del->content);
			del->content = NULL;
			free(del);
			del = NULL;
		}
		else
			tmp = tmp->next;
	}
}

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

static void	set_join_flag(t_lex *lex, t_token *token)
{
//	printf("char: %c\n", lex->c);

	token->join = false;
	if (lex->expansion == true)
	{
		if (lex->c == SINGLE_QUOTE || lex->c == DOUBLE_QUOTE || lex->c == DOLLAR)
			token->join = true;
	}
	printf("char: %c	flag:	%d token:	%s\n", lex->c, token->join, token->content);
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
	set_join_flag(lex, tmp);
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
		else if (lex->c == DOUBLE_QUOTE)
			handle_double_quotes(data, lex);
		else
			handle_words(data, lex);
	}
}
