/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:42:02 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/23 10:17:28 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

//TODO: sorry, has to comment it - ft_getenvp argument may be wrong... - refactor please :)
int cd(t_data *data)
{
	int ret;

//	if (!data->builtins->command[1])
//	{
//		ret = chdir(ft_getenvp(data, "HOME"));
//		return (EXIT_SUCCESS);
//	}
	ret = chdir(data->builtins->command[1]);
	if (ret != 0)
	{
		print_error(9);
		printf("%s\n", data->builtins->command[1]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
