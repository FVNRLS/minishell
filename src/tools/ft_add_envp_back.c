/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_envp_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:33:54 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/23 10:17:28 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*
	Add the node to the end of the stack.
	If the list doesn't exist yet, initialize the list with the node,
	so the node becomes the first element of the stack.
*/
void	ft_add_envp_back(t_envp **lst, t_envp *new)
{
	t_envp	*tmp;

	tmp = NULL;
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
