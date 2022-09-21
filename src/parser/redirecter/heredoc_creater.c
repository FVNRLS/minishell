/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_creater.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:38:03 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/21 13:11:56 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

static int count_heredoc_files(t_data *data)
{
	t_token	*tmp;
	int 	i;

	tmp = data->tokens;
	if (!tmp)
		return (0);
	i = 0;
	while (tmp != NULL && tmp->flag != T_PIPE)
	{
		if (tmp->flag == T_HEREDOC)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static void	add_heredoc(t_data *data, int i)
{
	char 	*path;
	char 	*index;
	char 	*name;

	path = ft_strdup("/tmp/.");
	index = ft_itoa(i);
	name = ft_strjoin(path, index);
	free(index);
	index = NULL;
	data->fd->hdoc[i] = name;
}

void	create_heredoc_files(t_data *data)
{
	t_token	*tmp;
	int		i;
	int 	cnt;

	cnt = count_heredoc_files(data);
	if (cnt == 0)
		return;
	else
		data->fd->hdoc = ft_calloc((cnt + 1), sizeof(char));
	i = 0;
	tmp = data->tokens;
	while (tmp != NULL && tmp->flag != T_PIPE)
	{
		if (tmp->flag == T_HEREDOC)
		{
			add_heredoc(data, i);
			i++;
		}
		tmp = tmp->next;
	}
}