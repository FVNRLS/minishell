/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleansplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:40:27 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/18 14:47:35 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_cleansplit(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	while (i > 0)
	{
		free(split[--i]);
		split[i] = NULL;
	}
	free(split);
	split = NULL;
}