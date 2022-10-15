/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_merger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:14:25 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/15 12:33:46 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/* 	Checks the join flag and sets it to 0 if there is redirection with flag 1
	and not a word token after it.
*/
void	refactor_join_flags(t_data *data)
{
	t_token	*tmp;

	tmp = data->tokens;
	while (tmp->next != NULL)
	{
		if (tmp->join == 1 && tmp->next->flag != T_WORD)
			tmp->join = 0;
		tmp = tmp->next;
	}
}

/* 	
	iterates all tokens and merges the current token with the next if it's
	join flag is set to true. The content of join-able token is merged with
	content of the next token.
*/
void	merge_joinable_tokens(t_data *data)
{
	t_token	*tmp;
	t_token	*del;

	tmp = data->tokens;
	if (!tmp)
		return ;
	refactor_join_flags(data);
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
	tmp->join = 0;
}

/* 	
	merge a redirection with the next word token. The word token content becomes
	content of the redirection token.
*/
void	merge_redirections(t_data *data)
{
	t_token	*tmp;
	t_token	*merge;
	bool	is_redir;

	tmp = data->tokens;
	if (!tmp)
		return ;
	while (tmp != NULL)
	{
		is_redir = check_redir(data, tmp->flag);
		if (is_redir == true)
		{
			merge = tmp->next;
			if (check_redir_syntax_error(data, tmp) == true)
				return ;
			free(tmp->content);
			tmp->content = NULL;
			tmp->content = merge->content;
			tmp->next = merge->next;
			free(merge);
			merge = NULL;
		}
		tmp = tmp->next;
	}
}

/* merges all word tokens next to each other into a bigger word token */
void	delete_words(t_data *data)
{
	t_token	*tmp;

	tmp = data->tokens;
	if (!tmp)
		return ;
	while (tmp != NULL && tmp->flag != T_PIPE)
	{
		tmp = tmp->next;
		free(data->tokens);
		data->tokens = tmp;
	}
}
