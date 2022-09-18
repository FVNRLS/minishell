/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:27:03 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/17 21:24:39 by jjesberg         ###   ########.fr       */
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

int	echo(t_data *data)
{
	int	i;
	char *s;

	s = data->tokens->content;
	if (!s || !s[5])
	{
		printf("\n");
		return (EXIT_SUCCESS);
	}
	i = 5;
	while (s[i] != NULL)
	{
		printf("%c", s[i++]);
	}
	printf("\n");
	return (EXIT_SUCCESS);
}