/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:48:57 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/07 12:48:57 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The bzero() function erases the data in the n bytes of the memory, starting
at the location pointed to by s, by writing zeros (bytes containing '\0')
to that area.*/

#include "../../incl/minishell.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*s1;

	s1 = (char *)s;
	i = 0;
	while (i < n)
	{
		s1[i] = '\0';
		i++;
	}
}
