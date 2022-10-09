/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 22:07:56 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/26 16:25:37 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	print_list(t_token *data)
{
	t_token	*tmp;
	int		len;

	len = 0;
	tmp = data;
	while (tmp != NULL)
	{
		len++;
		printf("%s\nflag = %i\n", tmp->content, tmp->flag);
		if (tmp->join)
			printf("join = true\n");
		else
			printf("join = false\n");
		tmp = tmp->next;
	}
	return (len);
}
