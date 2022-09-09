/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 16:46:39 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/09 19:54:30 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//TODO: edit!
static int	identify_flag(t_lex *lex)
{
	int flag;

	if (ft_strcmp(lex->buf, "<") == 0)
		flag = REDIRECT_IN;
	else if (ft_strcmp(lex->buf, ">") == 0)
		flag = REDIRECT_OUT;
	else if (ft_strcmp(lex->buf, ">>") == 0)
		flag = APPEND_IN;
	else if (ft_strcmp(lex->buf, "<<") == 0)
		flag = HEREDOC;
	else if (ft_strcmp(lex->buf, "|") == 0)
		flag = PIPE;
	else
		flag = WORD;
	return (flag);
}

static void	add_token(t_data *data, t_lex *lex)
{
	t_token	*tmp;
	int 	flag;
	char	*content;

	tmp = NULL;
	content = ft_strdup(lex->buf);
	if (!content)
		exit_with_free(data);
	flag = identify_flag(lex);
	tmp = ft_new_token(content, flag);
	ft_add_token_back(&data->tokens, tmp);
	free(lex->buf);
	lex->buf = NULL;
	lex->i++;
}


void	create_tokens(t_data *data, t_lex *lex)
{
	while (data->input[lex->i] != '\0')
	{
		lex->c = data->input[lex->i];
		if (data->input[lex->i] == DELIMITER)
			add_token(data, lex);
		else if (lex->c == SINGLE_QUOTE)
			handle_single_quotes(data, lex);
		else if ()
		else
		{
			lex->buf = ft_join_char(lex->buf, lex->c);
			lex->i++;
		}
	}
	add_token(data, lex);
}