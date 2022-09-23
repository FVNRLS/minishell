/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:42:02 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/23 14:03:56 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

//TODO: sorry, has to comment it - ft_getenvp argument may be wrong... - refactor please :)
int cd(t_data *data)
{
	int ret;
	t_envp *tmp;

	if (!data->builtins->command[1])
	{
		tmp = ft_getenvp(data, "HOME");
		ret = chdir(tmp->key);
		return (EXIT_SUCCESS);
	}
	ret = chdir(data->builtins->command[1]);
	if (ret != 0)
	{
		print_error(9);
		printf("%s\n", data->builtins->command[1]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
