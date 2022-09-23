/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:27:03 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/23 16:18:22 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	echo(t_data *data)
{
	int		i;
	int		splitlen;

	printf("data: %s\n", data->tokens->content);
	splitlen = ft_splitlen(data->builtins->command);
	if (splitlen == 1)
	{
		printf("\n");
		return (EXIT_SUCCESS);
	}
	i = 1;
	if (data->builtins->command[1] \
	&& ft_strcmp(data->builtins->command[1], "-n") == 0)
		i = 2;
	while (data->builtins->command[i])
		printf("%s ", data->builtins->command[i++]);
	if (data->builtins->command[1] \
	&& ft_strcmp(data->builtins->command[1], "-n") != 0)
		printf("\n");
	return (EXIT_SUCCESS);
}