/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:42:02 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/06 19:21:23 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int cd(char *path)
{
    int ret;

    if (!path || !path[0])
        return (error("Error in cd.c\n", 2));
    ret = chdir(path);
    if (ret != 0)
        return (error("Error in cd.c\n", 2));
    return (0);
}