/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:37:17 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/26 17:24:30 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_get_builtin(t_data *data)
{
	data->builtins->command = ft_split(data->tokens->content, ' ');
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[0]) == 0)
		return (0);
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[1]) == 0)
		return (1);
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[2]) == 0)
		return (2);
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[3]) == 0)
		return (3);
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[4]) == 0)
		return (4);
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[5]) == 0)
		return (5);
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[6]) == 0)
		return (6);
	ft_cleansplit(data->builtins->command);
	data->builtins->command = NULL;
	return (-1);
}