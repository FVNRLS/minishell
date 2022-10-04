/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:12:51 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/04 15:02:16 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	true_env(t_data *data)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (tmp->key[0])
		{
			if (ft_strlen(tmp->val) != 0)
				printf("1declare -x %s=\"%s\"\n", tmp->key, tmp->val);
			else
				printf("declare -x %s=\"\"\n", tmp->key);
		}
		tmp = tmp->next;
	}
}

void	check_keys(char **s)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i] && i < ft_splitlen(s))
	{
		j = 0;
		if (!ft_isalpha(s[i][j]) && s[i][j] != '_')
			built_error(EXPORT_ERROR, s[i]);
		while (s[i] != NULL && s[i][j + 1])
		{
			j++;
			if (s[i][j] == '=' || (s[i][j] == '+' \
			&& j < (int)ft_strlen(s[i]) && s[i][j + 1] == '='))
				break ;
			if (!ft_isalpha(s[i][j]) && !ft_isdigit((int)s[i][j]) \
			&& s[i][j] != '_')
			{
				built_error(EXPORT_ERROR, s[i]);
				break ;
			}
		}
		i++;
	}
}

int	check_string(t_data **data, int *i)
{
	char	*s;

	s = (*data)->tokens->content;
	if (ft_strlen(s) == 6 || !(*data)->builtins->command[1])
		return (EXIT_FAILURE);
	while (ft_isprint(s[*i]))
		(*i)++;
	(*i)++;
	ft_cleansplit((*data)->builtins->command);
	(*data)->builtins->command = ft_split(s + (*i), ' ');
	return (EXIT_SUCCESS);
}

static int	true_key(char *s)
{
	int	i;

	i = 1;
	if (!s || ft_strlen(s) < 1)
		return (0);
	if (s[0] != '_' && !ft_isalpha(s[0]))
		return (0);
	while (s[i])
	{
		if ((s[i] == '=' && i != 0) || (s[i] == '+' \
		&& s[i + 1] && s[i + 1] == '=' && i != 0))
			return (1);
		else if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]) && s[i] != '_' && i != 0)
			return (0);
		i++;
	}
	return (1);
}

char	*make_key(char *s, int *i)
{
	char	*key;

	key = NULL;
	if (!true_key(s))
		return (key);
	while (s[*i])
	{
		if (s[*i] == '=' || s[*i] == '+')
			break ;
		(*i)++;
	}
	key = malloc(sizeof(char) * ((*i) + 1));
	key[(*i)] = '\0';
	*i = 0;
	while (s[(*i)])
	{
		if (s[(*i)] == '=' || s[*i] == '+')
			break ;
		key[(*i)] = s[(*i)];
		(*i)++;
	}
	return (key);
}
