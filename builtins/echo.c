/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:27:03 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/20 19:00:32 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	pipe_pos(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '|')
			return (i + 6);
		i++;
	}
	return (5);
}

int	get_splitlen(char **s)
{
	int	count;

	count = 0;
	while (s && s[count] && s[count][0])
		count++;
	return (count);
}

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
	if (!data->builtins->command[1] \
	&& ft_strcmp(data->builtins->command[1], "-n") != 0)
		printf("\n");
	return (EXIT_SUCCESS);
}