/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:47:27 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/19 13:29:34 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	check_fork(t_data *data, int fd[2])
{
	return (1);
}

void	*exec_loop(t_data *data, char *pip)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (NULL);
	if (!check_fork(data, fd))
		return (NULL);
	close(fd[1]);
	return (NULL);
}
/*
errrors in message printer && define macros for error in errror.h
*/
void	exec_commands(t_data *data)
{
	t_token *tmp;
	int		mod;

	data->exec_error = false;
	tmp = (t_token*)data->tokens;
	while (data->tokens && data->exit_minishell != true)
	{
		if (data->tokens->content[0] == '|' && data->tokens->next)
			data->tokens = data->tokens->next;
		else if (data->tokens->content[0] == '|' && !data->tokens->next)
		{
			/*
			bash exit | exit 1 |
			should work and end here 
			cause the last pipe wait for input
			atm we get:
			minishell: syntax error near unexpected token `|'
			*/
			printf("start pipe loop\n");
			exec_loop(data, data->tokens->content);
		}
		mod = ft_isbuiltin(data);
		printf("mod = %i\n", mod);
		if (mod == -1)
		{
			print_error(7);
			printf("%s\n", data->builtins->command[0]);
			ft_cleansplit(data->builtins->command);
			return ;
		}
		data->builtins->funcs[mod - 1](data);
		ft_cleansplit(data->builtins->command);
		data->tokens = data->tokens->next;
	}
}