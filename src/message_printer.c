/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_printer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:06:29 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/09 19:14:05 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

//TODO: delete before submission!
void	print_tokens(t_data *data)
{
	t_token	*tmp;
	int 	i;

	tmp = data->tokens;
	i = 1;
	while (tmp != NULL)
	{
		printf("Token: %d	| 	content: %s	|	flag: %d\n", i, tmp->content, tmp->flag);
		tmp = tmp->next;
		i++;
	}
}
