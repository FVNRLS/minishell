/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenvp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:15:18 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/21 19:15:28 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*ft_getenvp(t_data *data, char *find)
{
	t_envp *tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, find) == 0)
			return (tmp->val);
		tmp = tmp->next;
	}
	return (NULL);
}