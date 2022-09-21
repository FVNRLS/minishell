/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:29:55 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/21 20:04:53 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	export(t_data *data)
{
	printf("data = %s\n", data->builtins->command[1]);
	char	**split;

	split = ft_split(data->builtins->command[1], '=');
	printf("split = %s\n", split[0]);
	//if (data->builtins->command[1])
	//if (ft_getenvp(data, ))
}
