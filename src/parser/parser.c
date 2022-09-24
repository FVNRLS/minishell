/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:20:38 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/24 17:26:44 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	parse_tokens(t_data *data)
{
	data->parse_error = false;
	init_fd(data);
	init_exec(data);
	check_multiple_pipes(data);
	if (data->parse_error == true)
		return ;
	merge_joinable_tokens(data);
	merge_redirections(data);
	merge_words(data);
	parse_hdocs(data);
	if (data->parse_error == true)
		return ;
}