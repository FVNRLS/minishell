/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:29:55 by jjesberg          #+#    #+#             */
/*   Updated: 2022/10/04 15:02:38 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

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
	char	*key;
	char	*val;
	int		i;
	t_envp	*new;
	t_envp	*list;

	val = NULL;
	list = (*data)->envp;
	i = 0;
	key = make_key(s, &i);
	if (key == NULL)
		return ;
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

bool	check_plus(char *s)
{
	int	i;
	int plus;

	plus = 0;
	i = 0;
	while (s[i + 1])
	{
		if (s[i] == '+' && s[i + 1] == '=')
			return (true);
		if (s[i] == '=')
			break ;
		i++;
	}
	return (false);
}

static void	key_export(t_data **data)
{
	int	i;
	int	plus;

	plus = 0;
	i = 0;
	while ((*data)->builtins->command[i])
	{
		if (ft_haschar((*data)->builtins->command[i], '+') && \
		check_plus((*data)->builtins->command[i]))
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
	if (data->builtins->command[1] \
	&& flag_check(data->builtins->command[1], 2))
		return (EXIT_FAILURE);
	if (check_string(&data, &i))
		true_env(data);
	if (i == 0)
		return (EXIT_FAILURE);
	check_keys(data->builtins->command);
	key_export(&data);
	return (EXIT_SUCCESS);
}
