/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:20:38 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/23 15:06:46 by rmazurit         ###   ########.fr       */
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
}