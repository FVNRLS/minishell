/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:31:39 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/12 19:31:39 by rmazurit         ###   ########.fr       */
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