/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:44:31 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/07 13:45:00 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/* Takes as a parameter a node and frees the memory of the node’s content
using the function ’del’ given as a parameter and free the node. The memory of
’next’ must not be freed. */

void	ft_lstdelone(t_envp *lst)
{
	if (!lst)
		return ;
	free(lst->key);
	free(lst->val);
	free(lst);
}