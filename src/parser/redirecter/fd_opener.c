/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_opener.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:29:57 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/21 13:34:41 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void	redirect_in(t_data *data, t_token *token)
{
	close_unused_fd_in(data);
	if (data->parse_error == true)
		return ;
	data->fd->fd_in = open(token->content, O_RDONLY);
	check_read_error(data, token);
}

void	redirect_from_heredoc(t_data *data, t_token *token)
{
	close_unused_fd_in(data);
	if (data->parse_error == true)
		return ;
	data->fd->fd_in = open(data->fd->hdoc[data->fd->hdoc_index],
						   O_CREAT | O_RDWR | O_TRUNC, RIGHTS);
	check_read_error(data, token);

	//later: unlink "/tmp/.tmp"
}

void	redirect_out(t_data *data, t_token *token)
{
	close_unused_fd_out(data);
	if (data->parse_error == true)
		return ;
	data->fd->fd_out = open(token->content, O_CREAT | O_RDWR | O_TRUNC, RIGHTS);
	check_create_error(data, token);
}

void	append(t_data *data, t_token *token)
{
	close_unused_fd_out(data);
	if (data->parse_error == true)
		return ;
	data->fd->fd_out = open(token->content, O_CREAT | O_RDWR | O_APPEND, RIGHTS);
	check_create_error(data, token);
}