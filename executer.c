/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:47:27 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/16 13:37:50 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*check if token is a builtin command
and return index of functions_array
if token != command then ret -1
*/
int	is_builtin(t_data *data)
{
	if (ft_strcmp(data->tokens->content, data->builtins->names[0]) == 0)
		return (1);
	if (ft_strcmp(data->tokens->content, data->builtins->names[1]) == 0)
		return (2);
	if (ft_strcmp(data->tokens->content, data->builtins->names[2]) == 0)
		return (3);
	if (ft_strcmp(data->tokens->content, data->builtins->names[3]) == 0)
		return (4);
	if (ft_strcmp(data->tokens->content, data->builtins->names[4]) == 0)
		return (5);
	if (ft_strcmp(data->tokens->content, data->builtins->names[5]) == 0)
		return (6);
	if (ft_strcmp(data->tokens->content, data->builtins->names[6]) == 0)
		return (7);
	return (-1);
}

/*
errrors in message printer && define macros for error in errror.h
*/
void	exec_commands(t_data *data)
{
	data->exec_error = false;

	//char *cmd;
	//int	i;
	//int ret;

	/*i = 0;
	ret = 0;
	while (data->tokens->content[i] && data->tokens->content[i] != SPACE)
	{
		cmd = ft_join_char(cmd, data->tokens->content[i]);
		i++;
	}
	if (ret = is_builtin(cmd) != -1)
	{
		
	}*/
	
	//data->tokens->content == cmd evtl
	//exec builtin via index
	// wenn wrong return ;
	//data.token.next gucken
}