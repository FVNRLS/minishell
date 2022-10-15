/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:27:03 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/15 17:16:33 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	check_exit_code_request(t_data *data)
{
	char	**args;

	args = ft_split(data->tokens->content, SPACE);
	if (!args)
		return (EXIT_FAILURE);
	if (args[1] != NULL)
	{
		if (ft_strcmp(args[1], "$?") != 0)
			g_exit_code = EXIT_SUCCESS;
	}
	ft_cleansplit(args);
	args = NULL;
	return (g_exit_code);
}


static bool is_flag(t_token *token)
{
	int	i;

	i = 0;
	if (token->content[i] == '-')
	{
		i++;
		while (token->content[i] != '\0')
		{
			if (token->content[i] != 'n')
				return (false);
			i++;
		}
		if (token->content[0] == '-' && ft_strlen(token->content) == 1)
			return (false);
		else
			return (true);
	}
	return (false);
}

/*
echo without args will just print a new line
echo -n = without new line
echo text will print the text include a new line
*/
int	echo(t_data *data)
{
	int		i;
	int 	words;
	int 	flag;
	bool	check_flag;
	t_token *tmp;

	flag = 0;
	check_flag = false;
	words = ft_count_word_tokens(data);
	if (words == 1)
	{
		printf("\n");
		return (EXIT_SUCCESS);
	}
	i = 1;
	tmp = data->tokens->next;
	while (i < words)
	{
		if (is_flag(tmp) == true && check_flag != true)
		{
			flag = 1;
		}
		else
		{
			printf("%s", tmp->content);
			if (i < words - 1)
				printf(" ");
			check_flag = true;
		}
		i++;
		tmp = tmp->next;
	}
	if (flag == 0)
		printf("\n");
	g_exit_code = check_exit_code_request(data);
	return (g_exit_code);
}
