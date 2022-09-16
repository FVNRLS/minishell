/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:05:24 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/16 12:11:24 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	free_main(t_data **data)
{
	int i = 0;
	while (i < 7)
		free((*data)->builtins->names[i++]);
	free((*data)->builtins);
	free((*data)->envp->val);
	free((*data)->envp);
	free(*data);
}

t_data	*init_data_test(t_data *data)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->builtins = malloc(sizeof(t_builtins));
	data->envp = malloc(sizeof(t_envp));
	if (!data->builtins || !data->envp)
		return (NULL);
	data->builtins->names[0] = ft_strdup("echo");
	data->builtins->names[1] = ft_strdup("cd");
	data->builtins->names[2] = ft_strdup("pwd");
	data->builtins->names[3] = ft_strdup("export");
	data->builtins->names[4] = ft_strdup("unset");
	data->builtins->names[5] = ft_strdup("env");
	data->builtins->names[6] = ft_strdup("exit");
	data->envp->val = NULL;
	data->envp->key = NULL;
	data->envp->val = getenv("USER");
	data->envp->next = NULL;
	data->envp->val = getcwd(data->envp->val, 0);
	data->builtins->funcs[0] = (void *)&echo;
	data->builtins->funcs[1] = (void *)&cd;
	data->builtins->funcs[2] = (void *)&pwd;
	data->builtins->funcs[3] = (void *)&export;
	data->builtins->funcs[4] = (void *)&unset;
	data->builtins->funcs[5] = (void *)&env;
	data->builtins->funcs[6] = (void *)&exit;
	data->exit_minishell = false;
	data->envp->next = NULL;
	data->input = NULL;
	data->lex_error = false;
	data->sep = NULL;
	data->status = 0;
	return (data);
}

int main()
{
	t_data	*data;

	data = NULL;
	data = init_data_test(data);
	if (data->builtins->funcs[3](data))
	{
		free_main(&data);
		printf("error1\n");
		return (EXIT_FAILURE);
	}
	free_main(&data);
	printf("fine\n");
    return (EXIT_SUCCESS);
}
