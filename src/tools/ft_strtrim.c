/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:38:01 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/09 19:37:27 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Allocates memory with malloc() and returns a copy of str with the characters
specified in ’set’ removed from the beginning and the end of the string.
Returns the trimmed string / NULL if the allocation fails.
*/

#include "../../incl/minishell.h"

// check if the character should be trimmed 1 = true;

char	*ft_strtrim(char *str, char delim)
{
	int		i;
	int		start;
	int		end;
	char	*trim;

	if (!str)
		return (NULL);
	start = 0;
	while ((str[start] != '\0') && (str[start] == delim))
		start++;
	end = (int)ft_strlen(str);
	while ((end > start) && (str[end] == delim))
		end--;
	trim = malloc(sizeof(char) * (end - start + 1));
	if (!trim)
		return (NULL);
	i = 0;
	while (start < end)
	{
		trim[i] = str[start];
		i++;
		start++;
	}
	trim[i] = '\0';
	free(str);
	str = NULL;
	return (trim);
}