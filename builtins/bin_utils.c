/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:14:07 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/21 10:08:11 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int		ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int error(char *m, int error)
{
	int	i;

	i = 0;
    errno = error;
	while (m[i])
		i += write(1, &m[i], 1);
    perror(NULL);
    return (EXIT_FAILURE);
}

int	is_number(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	get_splitlen(char **s)
{
	int	count;

	count = 0;
	while (s && s[count] && s[count][0])
		count++;
	return (count);
}
