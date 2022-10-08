/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_tracker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:07:45 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/08 17:07:45 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	track_history(t_data *data)
{
	data->input = readline("minishell % ");
	if (data->input == NULL)
		printf("exit\n");
	add_history(data->input);
}
