/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_printer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:06:29 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/06 11:58:28 by rmazurit         ###   ########.fr       */
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
	printf("-----------------------------------------------------------------------------------------------------\n\n");
}

void	print_error(int error)
{
	if (error == SINGLE_QUOTE_MISSING)
		printf("minishell:	syntax error. Missing '\n");
	else if (error == DOUBLE_QUOTE_MISSING)
		printf("minishell:	syntax error. Missing \"\n");
	else if (error == EXIT_ERROR)
		printf("minishell: exit: too many arguments\n");
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

int	built_error(int error, char *s)
{
	if (error == EXPORT_ERROR)
		printf("minishell: export: %s: invalid key\n", s);
	else if (error == EXIT_ARG_ERROR)
		printf("minishell: exit: %s: numeric argument required\n", s);
	else if (error == CMD_ERROR)
		printf("minishell: command: %s: not found\n", s);
	else if (error == EXEC_ERROR)
		printf("minishell: %s: command not found\n", s);
	else if (error == PATH_ERROR)
		printf("minishell: %s: No such file or directory\n", s);
	else if (error == UNSET_ERROR)
		printf("minishell: unset: `%s': not a valid identifier\n", s);
	else if (error == PERMISSION_ERROR)
		printf("minishell: %s: Permission denied\n", s);
	return (1);
}
