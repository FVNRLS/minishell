/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:07:45 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/20 20:52:52 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int pwd(t_data *data)
{
    char    *path;

	path = NULL;

	if (data->tokens->content && data->tokens->next && ft_strcmp(data->tokens->next->content, "|") == 0)
		return (EXIT_SUCCESS);
    path = getcwd(path, 0);
    if (!path || errno != 0)
        return (error("Error in pwd.c\n", errno));
    printf("path = %s\n", path);
    free(path);
    return (EXIT_SUCCESS);
}
