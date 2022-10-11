/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:37:17 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/11 14:23:55 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_get_builtin(t_data *data)
{
	int ret;

	ret = 0;
	data->builtins->command = ft_split(data->tokens->content, ' ');
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[0]) == 0)
		ret = 0;
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[1]) == 0)
		ret = 1;
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[2]) == 0)
		ret = 2;
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[3]) == 0)
		ret = 3;
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[4]) == 0)
		ret = 4;
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[5]) == 0)
		ret = 5;
	if (ft_strcmp(data->builtins->command[0], data->builtins->names[6]) == 0)
		ret = 6;
	return (ret);
}
