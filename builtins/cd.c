/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:42:02 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/26 15:46:33 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/*
char *dl_equal(char *s) //need later to get right key cause the have an equal
{
	return (NULL);
}
*/

int	cd(t_data *data)
{
	int		ret;
	t_envp	*tmp;

	if (ft_splitlen(data->builtins->command) > 2)
	{
		built_error(CD_ARGS, "minishell");
		return (EXIT_FAILURE);
	}
	if (!data->builtins->command[1])
	{
		tmp = ft_getenvp(data, "HOME");
		ret = chdir(tmp->val);
		return (ret);
	}
	ret = chdir(data->builtins->command[1]);
	if (ret != 0)
	{
		built_error(CD_ARG_ERROR, data->builtins->command[1]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
