/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:21:54 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/09 11:24:46 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*ft_join_char(char *buf, char c)
{
	int		i;
	char	*join;

	if (!buf)
	{
		buf = ft_calloc(1, sizeof(char));
		if (!buf)
			return (NULL);
	}
	join = malloc(sizeof(char) * (ft_strlen(buf) + 2));
	if (!join)
		return (NULL);
	i = 0;
	while (buf[i] != '\0')
	{
		join[i] = buf[i];
		i++;
	}
	join[i] = c;
	i++;
	join[i] = '\0';
	free(buf);
	buf = NULL;
	return (join);
}