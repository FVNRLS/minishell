/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_printer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:06:29 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/26 11:51:01 by rmazurit         ###   ########.fr       */
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
	printf("-----------------------------------------------------------------------------------------------------\n\n");
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
		printf("minishell: exit: Too much arguments.\n");
	else if (error == INVALID_PATH)
		printf("minishell: Invalid file or directory:");
}

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
	free(redir);
	redir = NULL;
}

void	built_error(int error, char *s)
{
	if (error == EXPORT_ERROR)
		printf("minishell: export: »%s«: invalid key\n", s);
	else if (error == EXIT_ARG_ERROR)
		printf("minishell: exit: »%s«: numeric argument required\n", s);
	else if (error == CMD_ERROR)
		printf("minishell: command: »%s«: not found\n", s);
	else if (error == CD_ARG_ERROR)
		printf("minishell: »%s«: Invalid file or path.\n", s);
	else if (error == CD_ARGS)
		printf("%s: cd: Too much arguments\n", s);
}
