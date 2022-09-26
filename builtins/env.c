/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:41:46 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/26 16:33:13 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	env(t_data *data)
{
	t_envp	*tmp;

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
