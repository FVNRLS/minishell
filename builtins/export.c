/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:29:55 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/28 19:40:27 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	check_new(char **s)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i])
	{
		j = 0;
		if (!ft_isalphabet(s[i][j]))
			return (built_error(EXPORT_ERROR, s[i]));
		while (s[i][j + 1])
		{
			j++;
			if (s[i][j] == '=')
				break ;
			if (!ft_isalphabet(s[i][j]) && !ft_isdigit((int)s[i][j]))
				return (built_error(EXPORT_ERROR, s[i]));
		}
		i++;
	}
	return (0);
}

int	check_string(t_data **data, int *i)
{
	char	*s;

	s = (*data)->tokens->content;
	if (ft_strlen(s) == 6)
		return (EXIT_FAILURE);
	while (ft_isprint(s[*i]))
		(*i)++;
	(*i)++;
	ft_cleansplit((*data)->builtins->command);
	(*data)->builtins->command = ft_split(s + (*i), ' ');
	return (EXIT_SUCCESS);
}

void	make_envp(char *s, t_data **data)
{
	char 	*key;
	char	*val;
	int		i;
	t_envp	*new;
	t_envp *list;

	val = NULL;
	list = (*data)->envp;
	i = 0;
	key = make_key(s, &i);
	new = ft_getenvp(*data, key);
	if (s[i] != '\0' && s[i + 1] != '\0')
		val = ft_strdup(s + i + 1);
	if (val == NULL)
	{
		printf("empty malloc\n");
		val = ft_strdup("");
	}
	if (new != NULL)
	{
		free(key);
		if (ft_strlen(val) != 0)
		{
			free(new->val);
			new->val = val;
		}
		else
			free(val);
	}
	else
	{
		new = ft_new_envp(key, val);
		ft_add_envp_back(&list, new);
	}
}

void	key_export(t_data **data)
{
	int	i;

	i = 0;
	while ((*data)->builtins->command[i])
	{
		if ((*data)->builtins->command[i][0] == '=')
			i++;
		else if ((*data)->builtins->command[i])
		{
			make_envp((*data)->builtins->command[i], data);
			i++;
		}
	}
	
}

int	export(t_data *data)
{
	int	i;

	i = 0;
	if (check_string(&data, &i))
		true_env(data);
	if (i == 0)
		return (EXIT_FAILURE);
	if (check_new(data->builtins->command))
		return (EXIT_FAILURE);
	key_export(&data);
	return (EXIT_SUCCESS);
}
