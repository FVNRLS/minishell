/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:42:02 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/13 15:32:33 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int cd(char *val)
{
	int ret;

	if (!val || !val[0])
		return (error("Error in cd.c\n", 2));
	ret = chdir(val);
	if (ret != 0)
		return (error("Error in cd.c\n", 2));
	return (EXIT_SUCCESS);
}
