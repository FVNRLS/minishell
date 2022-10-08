/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:27:03 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/08 15:18:03 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static int	its_nflag(char *s, int *flag)
{
	int	i;

	i = 0;
	if (!s || !s[i])
		return (0);
	while (s[i])
	{
		if (s[i] != 'n' && s[i] != ' ' && i != 0)
			return (0);
		i++;
		if (s[i] == '\0' || s[i] == ' ')
		{
			*flag = i + 1;
			break ;
		}
	}
	return (1);
}

int	echo_pos_helper(int i, char *s, int *flag)
{
	while (s[i] && !ft_isprint(s[i]))
	{
		i++;
		if (s[i] && s[i] == '-')
		{
			i++;
			if (its_nflag(s + i, flag))
				return (i + *flag);
			break ;
		}
	}
	return (0);
}

/*
	get start pos for echo string
*/
int	echo_pos(char *s, int *flag)
{
	int	tmp;
	int	i;

	i = 0;
	while (s[i] && !ft_isprint(s[i]))
		i++;
	while (s[i])
	{
		if (!ft_isprint(s[i]))
			break ;
		i++;
	}
	tmp = echo_pos_helper(i, s, flag);
	if (tmp == 0)
		tmp = i + 1;
	return (tmp);
}

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

int	echo(t_data *data)
{
	int		i;
	int		flag;

	flag = 0;
	i = echo_pos(data->tokens->content, &flag);
	if (i && data->tokens->content \
	&& i < (int)ft_strlen(data->tokens->content))
		printf("%s", (data->tokens->content + i));
	if (!flag)
		printf("\n");
	g_exit_code = check_exit_code_request(data);
	return (g_exit_code);
}
