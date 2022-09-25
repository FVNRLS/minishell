/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:29:55 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/25 12:19:28 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	true_env(t_data *data)
{
	t_envp *tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (tmp->key[0] && tmp->val[0])
			printf("declare -x %s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
}

int	check_new(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i][0] == '=')
		{
			built_error(EXPORT_ERROR, s[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_string(t_data **data, int *i)
{
	int		tmp;
	char	*s;

	s = (*data)->tokens->content;
	tmp = 0;
	if (ft_strlen(s) == 6)
		return (EXIT_FAILURE);
	while (ft_isprint(s[*i]))
		(*i)++;
	(*i)++;
	ft_cleansplit((*data)->builtins->command);
	(*data)->builtins->command = ft_split(s + (*i), ' ');
	if (check_new((*data)->builtins->command))
	{
		i = 0;
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

int	export(t_data *data)
{
	int	i;

	i = 0;
	if (check_string(&data, &i))
		true_env(data);
	if (i == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
