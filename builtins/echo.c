/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:27:03 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/24 10:25:41 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/*
	norminette...
*/
int	echo_pos_helper(int i, char *s, int *flag)
{
	while (s[i] && !ft_isprint(s[i]))
	{
		i++;
		if (s[i] && s[i] == '-')
		{
			i++;
			if (s[i] && s[i] == 'n' && (!s[i + 1] || !ft_isprint(s[i + 1])))
			{
				*flag = 1;
				return (i + 2);
			}
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

int	echo(t_data *data)
{
	int		i;
	int		flag;

	flag = 0;
	i = echo_pos(data->tokens->content, &flag);
	if (i && data->tokens->content \
	&& i < ft_strlen(data->tokens->content))
		printf("%s", (data->tokens->content + i));
	if (!flag)
		printf("\n");
	return (EXIT_SUCCESS);
}
