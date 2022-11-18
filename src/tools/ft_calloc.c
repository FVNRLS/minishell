/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:47:40 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/07 12:47:40 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The C library function void *calloc(size_t nitems, size_t size) allocates
enough space for count objects that are size bytes.
The memory allocation is limited by SIZE_MAX (size_t), which depends on OS.
The difference in malloc and calloc is that malloc does not set the memory to
zero where as calloc sets allocated memory to zero.
if (size > 0 && (SIZE_MAX / size) < count)
		return (NULL); -----this check was ignored because of moulinette
This function returns a pointer to the allocated memory, or NULL if the request
fails. */

#include "../../incl/minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	void	*ptr;

	if (size > 0 && (SIZE_MAX / size) < count)
		return (NULL);
	total = size * count;
	ptr = malloc(total);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total);
	return (ptr);
}
