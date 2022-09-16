/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:20:38 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/15 16:22:56 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//TODO: continue with resolve redirections!


void	parse_tokens(t_data *data)
{
	data->parse_error = false;

	check_multiple_pipes(data);
	if (data->parse_error == true)
		return ;
	merge_joinable_tokens(data);
	merge_redirections(data);
	merge_words(data);
//	resolve_redirections(data);
	if (data->parse_error == true)
		return ;
}