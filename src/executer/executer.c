/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:47:27 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/19 18:53:58 by jjesberg         ###   ########.fr       */
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

int	check_pipe(t_data *data)
{
	if (data->tokens->content[0] == '|' && data->tokens->next)
	{
		//printf("skip cmd its a pipe\n");
		data->tokens = data->tokens->next;
		return (0);
	}
	return (1);
}

int	mod_error(t_data *data)
{
	if (1 && check_pipe(data))
	{
		print_error(7);
		//printf("%s\n", data->builtins->command[0]);
		ft_cleansplit(data->builtins->command);
		return (1);
	}
	return (0);	
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
		if (data->tokens->content[0] == '|' && !data->tokens->next)
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
		//printf("mod = %i\n", mod);
		if (mod == -1 && mod_error(data))
			break ;
		if (mod != -1)
		{
			data->builtins->funcs[mod - 1](data);
			data->tokens = data->tokens->next;
		}
		ft_cleansplit(data->builtins->command);
	}
}