/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_printer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:06:29 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/12 17:02:31 by rmazurit         ###   ########.fr       */
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
	printf("-----------------------------------------------------------------------------------------------------\n");
	printf("Token:	|	Flag:	|	Joinable:	|	Content:\n");
	printf("-----------------------------------------------------------------------------------------------------\n");
	while (tmp != NULL)
	{
		printf("%d	|	%d	|	%d		| 	%s\n", i, tmp->flag, tmp->join, tmp->content);
		tmp = tmp->next;
		i++;
	}
}

void	print_error(int error)
{
	if (error == SINGLE_QUOTE_MISSING)
		printf("Syntax error. Missing '\n");
	else if (error == DOUBLE_QUOTE_MISSING)
		printf("Syntax error. Missing \"\n");
}
