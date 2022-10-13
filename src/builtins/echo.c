/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:27:03 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/13 13:34:34 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	its_nflag(char *s, int *flag)
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

static int	echo_helper(t_data *data, int i, int flag)
{
	while (data->tokens->content[i + 1] && data->tokens->content[i] == '-' \
	&& data->tokens->content[i + 1] == 'n' \
	&& check_n(data->tokens->content + i))
	{
		i += echo_pos(data->tokens->content + i, &flag);
		if ((int)ft_strlen(data->tokens->content) <= i)
		{
			if (flag == 1)
				printf("\n");
			return (g_exit_code);
		}
	}
	if (i && data->tokens->content \
	&& i < (int)ft_strlen(data->tokens->content))
		printf("%s", (data->tokens->content + i));
	if (!flag)
		printf("\n");
	g_exit_code = check_exit_code_request(data);
	return (g_exit_code);
}

/*
echo without args will just print a new lline
echo -n = without new line
echo text will print the text include a new line
*/
int	echo(t_data *data)
{
	int		i;
	int		flag;

	flag = 0;
	if (ft_strlen(data->tokens->content) == 4)
	{
		printf("\n");
		return (g_exit_code);
	}
	i = echo_pos(data->tokens->content, &flag);
	if ((int)ft_strlen(data->tokens->content) <= i)
	{
		if (flag == 1)
			printf("\n");
		return (g_exit_code);
	}
	echo_helper(data, i, flag);
	g_exit_code = check_exit_code_request(data);
	return (g_exit_code);
}
