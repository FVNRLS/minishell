/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:49:28 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/11 19:51:51 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"


//TODO: continue here, check $? expansion
// elim. leaks!!!!  $CWD $PWD $PWD --> call 3 times causes a leak and a stupid junk node is created!
// something is wrong on processing winvalid expansion envps!
void	expand_last_return(t_lex *lex)
{
	char	*exit_code;
	char 	c;
	int		i;

	exit_code = ft_itoa(g_exit_code);
	lex->buf = ft_strjoin(lex->buf, exit_code);
	i = 1;
	while (lex->param[i] != '\0')
	{
		c = lex->param[i];
		lex->buf = ft_join_char(lex->buf, c);
		i++;
	}
}

void	try_expansion(t_data *data, t_lex *lex)
{
	t_envp	*tmp;

//	if (lex->param[0] == '?')
//	{
//		expand_last_return(lex);
//		return ;
//	}
	tmp = data->envp;
	while (tmp != NULL)
	{
		if (ft_strcmp(lex->param, tmp->key) == 0)
		{
			lex->buf = ft_strjoin(lex->buf, tmp->val);
			return ;
		}
		tmp = tmp->next;
	}
	lex->buf = ft_join_char(lex->buf, DOLLAR);
	lex->buf = ft_strjoin(lex->buf, lex->param);
}

void	expand_params(t_data *data, t_lex *lex)
{
	int	i;

	i = 0;
	while (lex->exp_items[i] != NULL)
	{
		lex->param = lex->exp_items[i];
		try_expansion(data, lex);
		i++;
	}
	if (lex->prev_content != NULL)
	{
		lex->prev_content = ft_strjoin(lex->prev_content, lex->buf);
		free(lex->buf);
		lex->buf = NULL;
		lex->buf = ft_strjoin(lex->buf, lex->prev_content);
	}
	lex->flag = WORD;
	add_token(data, lex);
}

void	split_to_exp_params(t_data *data, t_lex *lex)
{
	while (lex->c != DELIMITER && lex->c != '\0')
	{
		lex->buf = ft_join_char(lex->buf, lex->c);
		lex->i++;
		lex->c = data->input[lex->i];
	}
	lex->exp_items = ft_split(lex->buf, DOLLAR);
	free(lex->buf);
	lex->buf = NULL;
}

void	handle_expansion(t_data *data, t_lex *lex)
{
	char next_char;

	next_char = data->input[lex->i + 1];
	if (next_char == DELIMITER || next_char == '\0')
	{
		lex->buf = ft_join_char(lex->buf, DOLLAR);
		add_token(data, lex);
		lex->i++;
		return ;
	}
	if (lex->buf != NULL)
	{
		lex->prev_content = ft_strjoin(lex->prev_content, lex->buf);
		free(lex->buf);
		lex->buf = NULL;
	}
	split_to_exp_params(data, lex);
	expand_params(data, lex);
	free_expandable_items(lex);
	lex->i++;
}
