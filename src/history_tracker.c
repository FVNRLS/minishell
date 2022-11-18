/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_tracker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:07:45 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/13 16:51:04 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/* 
	Prompts a new user input and saves it to the data->input.
	In case of ctrl-d key-hook there is no input --> program exits!
*/
void	track_history(t_data *data)
{
	data->input = readline("minishell % ");
	if (!data->input)
	{
		printf("exit\n");
		free_all_ressources(data);
		exit(g_exit_code);
	}
	if (ft_strlen(data->input) != 0)
		add_history(data->input);
}
