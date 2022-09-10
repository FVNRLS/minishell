/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 20:30:04 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/10 20:30:51 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*ft_strjoin(char *buf, char *tmp)
{
	int		i;
	int		j;
	char	*join;

	if (!buf)
	{
		buf = ft_calloc(1, sizeof(char));
		if (!buf)
			return (NULL);
	}
	join = malloc(sizeof(char) * ((ft_strlen(buf) + ft_strlen(tmp)) + 1));
	if (!join)
		return (NULL);
	i = 0;
	while (buf[i] != '\0')
	{
		join[i] = buf[i];
		i++;
	}
	j = 0;
	while (tmp[j] != '\0')
		join[i++] = tmp[j++];
	join[i] = '\0';
	free(buf);
	buf = NULL;
	return (join);
}