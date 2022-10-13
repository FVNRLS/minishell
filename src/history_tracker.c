/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_tracker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:07:45 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/13 13:30:23 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/* 
	Prompts a new user input and saves it to the data->input.
	In case of ctrl-d keyhook there is no input --> program exits!
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
	add_history(data->input);
}
