/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:07:45 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/23 10:17:28 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int pwd(t_data *data)
{
    char    *path;

    path = NULL;
    path = getcwd(path, 0);
    if (!path)
        return (error("Error in pwd.c\n", errno));
    printf("path = %s\n", path);
    free(path);
    return (EXIT_SUCCESS);
}
