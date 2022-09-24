/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_duplicator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:38:26 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/24 17:26:15 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void	dup_infile_to_outfile(t_data *data)
{
	if (data->fd->in != STDIN_FILENO)
	{
		dup2(data->fd->in, STDIN_FILENO);
		close(data->fd->in);
	}
	if (data->fd->out != STDOUT_FILENO)
	{
		dup2(data->fd->out, STDOUT_FILENO);
		close(data->fd->out);
	}
}

void	redirect_in_out(t_data *data, t_token *token)
{
	if (!token)
		return ;
	if (token->next == NULL)
		dup_infile_to_outfile(data);
}