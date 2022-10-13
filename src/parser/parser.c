/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:20:38 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/13 12:42:15 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/* counts number of heredoc tokens in order to create an array of hdoc files */
static int	count_hdoc_files(t_data *data)
{
	t_token	*tmp;
	int		i;

	tmp = data->tokens;
	if (!tmp)
		return (0);
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->flag == T_HEREDOC)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

/* 
	Check for parsing errors and merge all tokens with true join-able flag
	Heredoc files has higher priority over the execution.
	--> creates and reads content into all hdocs files from hdoc-tokens.
	In case of parse_error the commands will not be executed at all.
*/
void	parse_tokens(t_data *data)
{
	int	cnt;

	data->parse_error = false;
	init_fd(data);
	check_multiple_pipes(data);
	if (data->parse_error == true)
		return ;
	merge_joinable_tokens(data);
	merge_redirections(data);
	if (data->parse_error == true)
		return ;
	merge_words(data);
	cnt = count_hdoc_files(data);
	if (cnt == 0)
		return ;
	else
	{
		data->fd->hdoc = malloc(sizeof(char *) * (cnt + 1));
		data->fd->hdoc[cnt] = NULL;
		parse_hdocs(data);
	}
}
