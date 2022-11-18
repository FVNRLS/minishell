/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:37:51 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/07 17:54:31 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/* Deletes and frees the given node and every successor (like next or content)
of that node, using the function ’del’ and free() from malloc.
Finally, the pointer to the list must be set to NULL.
lst: The address of a pointer to a node.
del: The address of the function used to delete the content of the node. */

void	ft_lstclear(t_envp **lst)
{
	t_envp	*tmp;

	if ((!lst) || (!*lst))
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
