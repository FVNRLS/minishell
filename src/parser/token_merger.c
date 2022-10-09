/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_merger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:14:25 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/15 13:56:26 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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

void	merge_words(t_data *data)
{
	t_token	*tmp;
	t_token	*del;

	tmp = data->tokens;
	if (!tmp)
		return ;
	del = NULL;
	while (tmp->next != NULL)
	{
		del = tmp->next;
		if (tmp->flag == T_WORD && del->flag == T_WORD)
		{
			tmp->content = ft_join_char(tmp->content, SPACE);
			tmp->content = ft_strjoin(tmp->content, del->content);
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
