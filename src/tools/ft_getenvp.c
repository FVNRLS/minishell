/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenvp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:15:18 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/26 00:02:50 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*
return NULL if find is a "new Var"
*/
t_envp	*ft_getenvp(t_data *data, char *find)
{
	t_envp *tmp;

	tmp = data->envp;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, find) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}