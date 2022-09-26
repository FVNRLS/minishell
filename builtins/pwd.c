/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:07:45 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/26 16:33:13 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"


//TODO: error handling... no error funtion error
int	pwd(t_data *data)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 0);
//	if (!path)
//		return (error("Error in pwd.c\n", errno));
	printf("path = %s\n", path);
	free(path);
	return (EXIT_SUCCESS);
}
