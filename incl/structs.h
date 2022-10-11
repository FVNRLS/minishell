/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:53:01 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/09 15:21:37 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

# define NUM_BUILTINS		7
# define NUM_REDIRECTIONS	4

typedef struct s_token
{
	char			*content;
	int				flag;
	bool			join;
	struct s_token	*next;
}		t_token;

typedef struct s_envp
{
	char			*key;
	char			*val;
	bool			equal;
	struct s_envp	*next;
}		t_envp;

typedef struct s_builtins
{
	char		*names[NUM_BUILTINS];
	int			(*funcs[NUM_BUILTINS])(void *);
	char		**command;
	char 		*home;
}		t_builtins;

typedef struct s_lex
{
	int		i;
	char	c;
	char	*buf;
	int		flag;
	bool	single_quote_mode;
	bool	double_quote_mode;
	bool	expansion;
}		t_lex;

typedef struct s_fd
{
	int		in;
	int		out;
	int		std_in;
	int		std_out;
	char	**hdoc;
	int		hdoc_index;
}		t_fd;

typedef struct s_exec
{
	char	**cmd;
	char	*path;
	int		cmd_num;
	int		last_cmd;
	bool	no_cmd;
}		t_exec;

typedef struct s_data
{
	t_builtins	*builtins;
	pid_t		pid;
	char		**env;
	char		*input;
	char		*sep;
	int			*redir;
	int			pipe[2];
	t_fd		*fd;
	t_envp		*envp;
	t_token		*tokens;
	t_exec		*exec;
	bool		lex_error;
	bool		parse_error;
	bool		exec_error;
	bool		exit_minishell;
}		t_data;

#endif
