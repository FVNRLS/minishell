/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:37:17 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/18 14:37:50 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*check if token is a builtin command
and return index of functions_array
if token != command then ret -1
*/
int	ft_isbuiltin(t_data *data)
{
	data->builtins->command = ft_split(data->tokens->content, ' ');
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[0]) == 0)
		return (1);
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[1]) == 0)
		return (2);
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[2]) == 0)
		return (3);
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[3]) == 0)
		return (4);
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[4]) == 0)
		return (5);
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[5]) == 0)
		return (6);
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[6]) == 0)
		return (7);
	return (-1);
}