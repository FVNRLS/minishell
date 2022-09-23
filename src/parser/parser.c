/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:20:38 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/23 13:46:41 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	parse_tokens(t_data *data)
{
	data->parse_error = false;
	init_fd(data);

	check_multiple_pipes(data);
	if (data->parse_error == true)
		return ;

	merge_joinable_tokens(data);
	merge_redirections(data);
	merge_words(data);

	parse_hdocs(data);
	if (data->parse_error == true)
		return ;

	resolve_redirections(data);
	destroy_hdocs(data);
	if (data->parse_error == true)
		return ;
	merge_words(data);
	//printf("fd_in:	%d	fd_out:	%d\n", data->fd->in, data->fd->out);


	close_fd_in_out(data); //perform in the end after exec
}