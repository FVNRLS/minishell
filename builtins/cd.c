/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:42:02 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/19 19:31:38 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/*
use opendir, readdir, closedir 
to figure out path is valid or not!
NOT FINISHED
*/
int	is_valid_path(char *path)
{
	return (1); 
}

int	is_pipe(char *s)
{
	int i;

	i = 0;
	if (s && s[0] == '|' && ft_strlen(s) == 1)
		return (1);
	return (0);
}

int	cd_args(t_data *data)
{
	t_token *list;

	list = data->tokens;
	while (data->tokens->next)
	{
		data->tokens = data->tokens->next;
		if (!is_valid_path(data->tokens->content) && !is_pipe(data->tokens->content))
			return (0);
		else if (is_valid_path(data->tokens->content) || is_pipe(data->tokens->content))
			return (1);
	}
	return (0);
}

int cd(t_data *data)
{
	int ret;
	int i;

	i = 0;
	if (cd_args(data))
		return (EXIT_FAILURE);
	if (data->builtins->command[1] && data->builtins->command[1][0] == '|')
		return (EXIT_SUCCESS);
	if (!data->builtins->command[1])
	{
		printf("chdir to HOME dir, not working atm\n");
		//ret = chdir(data.HOMEDIR??);
		return (EXIT_SUCCESS);
	}
	ret = chdir(data->builtins->command[1]);
	if (ret != 0)
	{
		print_error(9);
		printf("%s\n", data->builtins->command[1]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
