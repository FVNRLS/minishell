/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:07:45 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/06 17:59:48 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

//FLAGS -P avoid all symlinks (If no option is specified, -P is assumed!!!--->Wenn -L und -P beide angegeben sind, hat das letzte Vorrang.
//FLAGS -L use PWD from environment, even if it contains symlinks
//FLAGS --help ??
//FLAGS --version ??

int pwd(void)
{
    char    *path;

    path = NULL;
    path = getcwd(path, 10);
    if (!path || errno != 0)
        return (error("Error in pwd.c\n", errno));
    printf("path = %s\n", path);
    free(path);
    return (0);
}