/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_executer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:35:16 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/23 15:41:18 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void	exec_bash_commands(t_data *data)
{
	resolve_redirections(data);
	if (data->parse_error == true)
		return ;
	merge_words(data);
	//printf("fd_in:	%d	fd_out:	%d\n", data->fd->in, data->fd->out);
}