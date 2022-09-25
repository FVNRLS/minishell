/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:03:16 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/25 18:53:30 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	create_pipe(t_data *data)
{
	if (pipe(data->pipe) < 0)
	{
		perror(NULL);
		data->exec_error = true;
		return ;
	}
}

void	close_all_pipe_ends(t_data *data)
{
		close(data->pipe[1]);
		close(data->pipe[0]);
}

void	redirect_in_out(t_data *data, t_token *token)
{
	if (!token)
		return ;
	dup_in_to_out(data);
}