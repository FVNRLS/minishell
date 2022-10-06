/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_opener.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:29:57 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/06 12:08:43 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void	redirect_from_hdoc(t_data *data)
{
	char *hdoc;

	hdoc = data->fd->hdoc[data->fd->hdoc_index];
	close_unused_fd_in(data);
	if (data->parse_error == true)
		return ;
	data->fd->in = open(hdoc, O_RDONLY);
	if (access(hdoc, F_OK < 0))
	{
		built_error(PATH_ERROR, hdoc);
		data->parse_error = true;
	}
	else if (access(hdoc, R_OK) < 0)
	{
		built_error(PERMISSION_ERROR, hdoc);
		data->parse_error = true;
	}
}

void	redirect_in(t_data *data, t_token *token)
{
	close_unused_fd_in(data);
	if (data->parse_error == true)
		return ;
	check_fd_open_error(data, token);
	if (data->parse_error == true)
		return ;
	data->fd->in = open(token->content, O_RDONLY);
}

void	redirect_out(t_data *data, t_token *token)
{
	close_unused_fd_out(data);
	if (data->parse_error == true)
		return ;
	data->fd->out = open(token->content, O_CREAT | O_RDWR | O_TRUNC, RIGHTS);
	check_fd_create_error(data, token);
}

void	append(t_data *data, t_token *token)
{
	close_unused_fd_out(data);
	if (data->parse_error == true)
		return ;
	data->fd->out = open(token->content, O_CREAT | O_RDWR | O_APPEND, RIGHTS);
	check_fd_create_error(data, token);
}