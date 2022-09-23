/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 23:59:17 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/23 23:59:46 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*
deletes current token 
data.token = next
*/
void	ft_dl_token(t_data **data)
{
	t_token *tmp;

	tmp = (*data)->tokens;
	(*data)->tokens = (*data)->tokens->next;
	free(tmp->content);
	free(tmp);
}
