/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:14:07 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/19 00:25:40 by jjesberg         ###   ########.fr       */
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

char **dl_first(char **s)
{
	char 	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	new = malloc(sizeof(char *) * (i));
	while (s[j + 1])
	{
		new[j] = ft_strdup(s[j + 1]);
		j++;
	}
	new[j] = NULL;
	ft_cleansplit(s);
	return (new);
}