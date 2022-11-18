/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 20:25:53 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/10 20:25:53 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/* Allocates and returns a string representing the integer
received as an argument. Negative numbers must be handled.
Returns the string representing the integer. NULL if the allocation fails. */

static size_t	ft_count_size(int n)
{
	int	size;

	if (n > 0)
		size = 0;
	else
		size = 1;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	size_t	size;

	nbr = n;
	size = ft_count_size(n);
	if (nbr < 0)
		nbr *= -1;
	str = ((char *)malloc(size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	size--;
	while (nbr > 0)
	{
		str[size] = nbr % 10 + '0';
		nbr /= 10;
		size--;
	}
	if (size == 0 && str[1] == '\0')
		str[0] = '0';
	else if (size == 0 && str[1] != '\0')
		str[0] = '-';
	return (str);
}
