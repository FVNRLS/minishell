/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:31:39 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/13 12:01:28 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/* Creates a word (later command) token and sets the token flag to T_WORD */
void	handle_words(t_data *data, t_lex *lex)
{
	bool	redirect_found;

	lex->buf = ft_join_char(lex->buf, lex->c);
	lex->flag = T_WORD;
	lex->i++;
	lex->c = data->input[lex->i];
	redirect_found = find_redirections(lex);
	if (lex->c == SPACE || redirect_found == true || lex->c == '\0')
		add_token(data, lex);
}
