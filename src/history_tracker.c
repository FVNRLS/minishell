/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_tracker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:07:45 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/08 15:27:48 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	track_history(t_data *data)
{
	data->input = readline("minishell % ");
	add_history(data->input);
	free(data->input);
	data->input = NULL;
}
