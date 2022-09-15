/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:29:55 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/15 17:24:24 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	export(t_data *data)
{
	t_envp *tmp;
	char	**ptr;

	tmp = data->envp;
	if (!tmp || !tmp->key)
	{	
		printf("export.c Error empty data"); // just for debug
		return (EXIT_FAILURE);
	}
	while (tmp)
	{
		ptr = &tmp->val;
		//change Val of getenv(save->key);
		//(*ptr)[5] = '\n'; // we can change it but realloc maybe is better
		printf("ptr = %s\n", (*ptr));
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}