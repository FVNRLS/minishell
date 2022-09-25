/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:07:45 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/26 00:29:31 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	pwd(t_data *data)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 0);
	if (!path)
		return (error("Error in pwd.c\n", errno));
	printf("path = %s\n", path);
	free(path);
	return (EXIT_SUCCESS);
}
