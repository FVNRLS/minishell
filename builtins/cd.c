/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:42:02 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/19 13:30:53 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int cd(t_data *data)
{
	int ret;

	if (!data->builtins->command[1])
	{
		printf("chdir to HOME dir, not working atm\n");
		//ret = chdir(data.HOMEDIR??);
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
