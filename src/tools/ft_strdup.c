/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:07:34 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/07 19:08:08 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Returns a pointer to a null-terminated byte string, which is a duplicate of
str pointed to by str. The returned pointer must be passed to free to
avoid a memory leak.
If an error occurs, a null pointer is returned. */

#include "../../incl/minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;
	size_t	i;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}