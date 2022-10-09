/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_num_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:56:41 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/30 12:56:45 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_get_num_cmds(t_data *data)
{
	t_token	*tmp;
	int		i;

	tmp = data->tokens;
	i = 1;
	while (tmp != NULL)
	{
		if (tmp->flag == T_PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
