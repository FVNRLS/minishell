/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_printer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:06:29 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/23 10:20:25 by rmazurit         ###   ########.fr       */
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
		printf("minishell:	syntax error. Missing '\n");
	else if (error == DOUBLE_QUOTE_MISSING)
		printf("minishell:	syntax error. Missing \"\n");
	else if (error == EXIT_ERROR)
		printf("minishell: exit: Zu viele Argumente.\n");
	else if (error == EXIT_ARG_ERROR)
		printf("minishell: exit: d2: numeric argument required\n");
	else if (error == CMD_ERROR)
		printf("minishell: command not found:");
	else if (error == INVALID_PATH)
		printf("minishell: Invalid file or directory:");
	else if (error == CD_ARG_ERROR)
		printf("minishell: cd: Zu viele Argumente.\n");
	else if (error == EXPORT_ERROR)
		printf("minishell: export: Ist kein gültiger Bezeichner: ");
}

//TODO: use perror() or own error printer?

void	print_token_error(int error, t_token *token)
{
	char *redir;

	if (token->next == NULL)
		redir = ft_strdup("newline");
	else
		redir = ft_strdup(token->next->content);

	if (error == PIPE_SYNTAX_ERROR)
		printf("minishell: syntax error near unexpected token `|'\n");
	else if (error == REDIR_SYNTAX_ERROR)
		printf("minishell: syntax error near unexpected token `%s'\n", redir);
	else if (error == OPEN_ERROR)
		printf("minishell: %s: No such file or directory\n", token->content);
	free(redir);
	redir = NULL;
}
