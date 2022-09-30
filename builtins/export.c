/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:29:55 by jjesberg          #+#    #+#             */
/*   Updated: 2022/09/30 17:03:46 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	**dl_that(char **s, int i)
{
	char **new;
	int	j;
	int	k;

	k = 0;
	j = 0;
	new = malloc(sizeof(char *) * (ft_splitlen(s)));
	while (s[j])
	{
		if (j == i)
			j++;
		new[k] = ft_strdup(s[j]);
		j++;
		k++;
	}
	new[k] = NULL;
	return (new);
}

static int	check_new(char **s)
{
	int	i;
	int	j;
	char **tmp;

	j = 0;
	i = 0;
	while (s[i])
	{
		j = 0;
		if (!ft_isalpha(s[i][j]) && s[i][j] != '_')
		{
			built_error(EXPORT_ERROR, s[i]);
			tmp = dl_that(s, i);
			check_new(tmp);
			ft_cleansplit(tmp);
			break ;
		}	
		while (s[i][j + 1])
		{
			j++;
			if (s[i][j] == '=' || (s[i][j] == '+' \
			&& j < (int)ft_strlen(s[i]) && s[i][j + 1] == '='))
				break ;
			if (!ft_isalpha(s[i][j]) && !ft_isdigit((int)s[i][j]) && s[i][j] != '_')
			{
				printf("here2\n");
				return (built_error(EXPORT_ERROR, s[i]));
			}
		}
		i++;
	}
	return (0);
}

static int	check_string(t_data **data, int *i)
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

static char	*make_val(char *s, int i, int plus)
{
	char	*val;

	val = NULL;
	if (s[i] != '\0' && s[i + 1] != '\0' && !plus)
		val = ft_strdup(s + i + 1);
	else if (s[i] != '\0' && s[i + 1] != '\0' && plus)
	{
		i++;
		if (s[i] != '\0' && s[i + 1] != '\0')
			val = ft_strdup(s + i + 1);
	}
	if (val == NULL)
		val = ft_strdup("");
	return (val);
}

static void	old_key(t_envp *new, char *val, char *key, int plus)
{
	free(key);
	if (ft_strlen(val) != 0)
	{
		if (plus)
		{
			new->val = ft_strjoin(new->val, val);
			free(val);
			return ;
		}
		free(new->val);
		new->val = val;
	}
	else
		free(val);
}

static void	make_envp(char *s, t_data **data, int plus)
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
	val = make_val(s, i, plus);
	if (new != NULL)
		old_key(new, val, key, plus);
	else
	{
		new = ft_new_envp(key, val);
		ft_add_envp_back(&list, new);
	}
}

static void	key_export(t_data **data)
{
	int	i;
	int plus;

	plus = 0;
	i = 0;
	while ((*data)->builtins->command[i])
	{
		if (ft_haschar((*data)->builtins->command[i], '+'))
			plus = 1;
		make_envp((*data)->builtins->command[i], data, plus);
		i++;
		plus = 0;
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
