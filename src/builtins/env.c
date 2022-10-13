/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:41:46 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/13 13:48:35 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*
prints all ENVP which has a value
*/
int	env(t_data *data)
{
	t_envp	*tmp;

	if (data->builtins->command[1])
	{
		print_error(ENV_ERROR);
		return (CMD_NOT_FOUND);
	}
	tmp = data->envp;
	while (tmp != NULL)
	{
		if (tmp->key[0] && tmp->val[0])
		{
			printf("%s=%s\n", tmp->key, tmp->val);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
