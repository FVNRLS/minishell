/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_creater.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:38:03 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/21 16:27:59 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

static int count_hdoc_files(t_data *data)
{
	t_token	*tmp;
	int 	i;

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

static void	read_to_hdoc(t_data *data, t_token *token)
{
	char	*input;
	char	*limiter;
	int		lim_len;
	bool	limiter_found;

	limiter = ft_strjoin(ft_strdup(token->content), "\n");
	lim_len = ft_strlen(limiter) + 1;
	limiter_found = false;
	while (limiter_found != true)
	{
		input = readline(STDIN_FILENO);
		if (!input)
			break ;
		if (ft_strncmp(input, limiter, lim_len) == 0)
			limiter_found = true;
		else if (write(data->fd->in, input, ft_strlen(input)) < 0)
		{
			print_token_error(OPEN_ERROR, token);
			data->parse_error = true;
			return ;
		}
		free(input);
		input = NULL;
	}
	free(limiter);
	limiter = NULL;
}

static void	create_hdoc(t_data *data, t_token *token)
{
	char 	*path;
	char 	*index;
	char 	*name;

	path = ft_strdup("/tmp/");
	index = ft_itoa(data->fd->hdoc_index);
	name = ft_strjoin(path, index);
	free(index);
	index = NULL;
	data->fd->hdoc[data->fd->hdoc_index] = name;
	data->fd->in = open(data->fd->hdoc[data->fd->hdoc_index],
   		O_CREAT | O_RDWR | O_TRUNC, RIGHTS);
	check_read_error(data, token);
}

void	read_from_all_hdocs(t_data *data)
{
	t_token	*tmp;
	int 	cnt;

	cnt = count_hdoc_files(data);
	if (cnt == 0)
		return;
	else
	{
		data->fd->hdoc = malloc(sizeof(char *) * (cnt + 1));
		data->fd->hdoc[cnt] = NULL;
	}
	data->fd->hdoc_index = 0;
	tmp = data->tokens;
	while (tmp != NULL)
	{
		if (tmp->flag == T_HEREDOC)
		{
			create_hdoc(data, tmp);
			read_to_hdoc(data, tmp);
			close(data->fd->in);
			data->fd->hdoc_index++;
		}
		tmp = tmp->next;
	}
}