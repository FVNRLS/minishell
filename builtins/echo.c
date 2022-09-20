/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:27:03 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/20 20:38:30 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	echo(t_data *data)
{
	int		i;
	int		splitlen;

	splitlen = get_splitlen(data->builtins->command);
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