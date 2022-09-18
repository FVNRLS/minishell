/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 22:07:56 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/17 22:15:27 by jjesberg         ###   ########.fr       */
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
		printf("%s\nflag = %i\n", tmp->content);
		if (tmp->join)
			printf("join = true\n");
		else
			printf("join = false\n");
		tmp = tmp->next;
	}
	return (len);
}