/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_duplicator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:38:26 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/25 18:53:30 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	dup_in_to_out(t_data *data)
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
