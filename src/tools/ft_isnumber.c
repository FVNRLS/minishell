/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:05:32 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/28 17:28:38 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	init_minus(int *minus, int *i, char *s)
{
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*minus = 1;
		(*i)++;
	}
}

int	ft_isnumber(char *s, long long sum, int i)
{
	int				minus;

	minus = 0;
	init_minus(&minus, &i, s);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		sum += s[i] - '0';
		sum *= 10;
		if (sum >= 922337203685477580 && i < (int)ft_strlen(s) \
		&& s[i + 1] >= 8 + '0' && minus == 0)
			return (0);
		if (sum >= 922337203685477580 && i < (int)ft_strlen(s) \
		&& s[i + 1] >= 9 + '0' && minus == 1)
			return (0);
		i++;
	}
	return (1);
}
