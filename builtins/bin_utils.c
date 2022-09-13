/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:14:07 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/13 17:38:24 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int error(char *m, int error)
{
	int	i;

	i = 0;
    errno = error;
	while (m[i])
		i += write(1, &m[i], 1);
    perror(NULL);
    return (EXIT_FAILURE);
}
