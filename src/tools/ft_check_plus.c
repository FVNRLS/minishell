/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_plus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:06:27 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/04 15:09:55 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

bool	ft_check_plus(char *s)
{
	int	i;

	i = 0;
	while (s[i + 1])
	{
		if (s[i] == '+' && s[i + 1] == '=')
			return (true);
		if (s[i] == '=')
			break ;
		i++;
	}
	return (false);
}
