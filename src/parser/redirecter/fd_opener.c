/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_opener.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:29:57 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/13 13:18:29 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

/* 	
	closes previous opened, unsused fd_in and opens a heredoc file in read mode.
	if there is permisision or file error occured - the parse_error flag
	is set to true. 	
*/
void	redirect_from_hdoc(t_data *data)
{
	char	*hdoc;

	hdoc = data->fd->hdoc[data->fd->hdoc_index];
	close_unused_fd_in(data);
	if (data->parse_error == true)
		return ;
	data->fd->in = open(hdoc, O_RDONLY);
	if (access(hdoc, F_OK < 0))
	{
		exec_error(PATH_ERROR, hdoc);
		data->parse_error = true;
	}
	else if (access(hdoc, R_OK) < 0)
	{
		exec_error(PERMISSION_ERROR, hdoc);
		data->parse_error = true;
	}
}

/* 	
	closes previous opened, unsused fd_in and opens a file in read mode.
	if there is permisision or file error occured - the parse_error flag
	is set to true. 	
*/
void	redirect_in(t_data *data, t_token *token)
{
	close_unused_fd_in(data);
	if (data->parse_error == true)
		return ;
	data->fd->in = open(token->content, O_RDONLY);
	check_fd_open_error(data, token);
}

/* 
	closes previous opened, unsused fd_out.
	opens a file in overwrite mode or creates a new file.
	if there is permisision or file error occured - the parse_error flag
	is set to true. 	
*/
void	redirect_out(t_data *data, t_token *token)
{
	close_unused_fd_out(data);
	data->fd->out = open(token->content, O_CREAT | O_RDWR | O_TRUNC, RIGHTS);
	check_fd_create_error(data, token);
}

/* 	
	closes previous opened, unsused fd_out.
	opens a file in append mode or creates a new file if there is no such file.
	if there is permisision or file error occured - the parse_error flag
	is set to true. 	
*/
void	append(t_data *data, t_token *token)
{
	close_unused_fd_out(data);
	data->fd->out = open(token->content, O_CREAT | O_RDWR | O_APPEND, RIGHTS);
	check_fd_create_error(data, token);
}
