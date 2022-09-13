/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:05:24 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/13 15:33:07 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	char	*dup;
	size_t	len;
	size_t	i;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	free_main(t_data **data)
{
	free((*data)->builtins->names[0]);
	free((*data)->builtins);
	free((*data)->envp->val);
	free((*data)->envp);
	free(*data);
}

t_data	*init_data_test(t_data *data)
{
	data = malloc(sizeof(t_data));
	data->builtins = malloc(sizeof(t_builtins));
	data->envp = malloc(sizeof(t_envp));
	data->builtins->names[0] = ft_strdup("echo");
	data->builtins->names[1] = NULL;
	data->envp->val = NULL;
	data->envp->key = NULL;
	data->envp->key = getenv("USER");
	data->envp->val = getcwd(data->envp->val, 0);
	data->builtins->funcs[0] = (int (*)(void *))env;
	data->builtins->funcs[1] = (int (*)(void *))cd;
	data->builtins->funcs[2] = (int (*)(void *))pwd;
	data->builtins->funcs[3] = NULL;
	data->exit_minishell = false;
	data->envp->next = NULL;
	data->input = NULL;
	data->lex_error = false;
	data->sep = NULL;
	data->status = 0;
	data->tokens = NULL;
	return (data);
}

int main()
{
	t_data	*data;

	data = init_data_test(data);
    if (env(data))
        return (EXIT_FAILURE);
	if (pwd())
		return (EXIT_FAILURE);
	if (cd(".."))
		return (EXIT_FAILURE);
	if (cd("incl"))
		return (EXIT_FAILURE);
	if (pwd())
		return (EXIT_FAILURE);
	printf("fine\n");
	free_main(&data);
    return (EXIT_SUCCESS);
}