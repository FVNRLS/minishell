/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:06:42 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/13 11:16:29 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	check_n(char *s)
{
	int	i;

	i = 0;
	if (s[i] != '-')
		return (0);
	while (s[++i])
	{
		if (s[i] != 'n')
		{
			if (s[i] == '\0' || s[i] == ' ')
				return (1);
			return (0);
		}
	}
	return (1);
}

int	check_exit_code_request(t_data *data)
{
	char	**args;

	args = ft_split(data->tokens->content, SPACE);
	if (!args)
		return (EXIT_FAILURE);
	if (args[1] != NULL)
	{
		if (ft_strcmp(args[1], "$?") != 0)
			g_exit_code = EXIT_SUCCESS;
	}
	ft_cleansplit(args);
	args = NULL;
	return (g_exit_code);
}
