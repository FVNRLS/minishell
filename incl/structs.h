/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:53:01 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/25 18:51:37 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>


#ifndef STRUCTS_H
# define STRUCTS_H

# define NUM_BUILTINS		7
# define NUM_REDIRECTIONS	4
# define RIGHTS				0644

typedef struct s_token //linked tokens
{
	char			*content;
	int				flag;
	bool			join;
	struct s_token	*next;
}		t_token;

typedef struct s_envp
{
	char 			*key; //eg. name of the variable
	char 			*val; //eg. path or value of the variable
	struct s_envp	*next;
}		t_envp;

typedef struct s_builtins
{
	char		*names[NUM_BUILTINS]; //strcmp the tokens with reserved words and if match - call the builtins on the sam index
	int 		(*funcs[NUM_BUILTINS])(void *); // builtin functions
	char		**command;
}		t_builtins;

typedef struct s_lex
{
	int 		i;
	char 		c;
	char 		*buf;
	int 		flag;
	bool		single_quote_mode;
	bool		double_quote_mode;
	bool		expansion;
}		t_lex;

typedef struct s_fd
{
	int 		in;
	int 		out;
	char 		**hdoc;
	int 		hdoc_index;
	bool		hdoc_used;
}	t_fd;

typedef struct s_exec
{
	char	**cmd;
	char	*path;
	int 	cmd_num;
	bool	pipe_used;
}		t_exec;


typedef struct s_data
{
	t_builtins	*builtins;
	int 		pid;
	char 		**env;
	char 		*input;
	char		*sep;
	int 		*redir;
	int 		pipe[2];
	t_fd 		*fd;
	t_envp		*envp; // linked list - contains all environments
	t_token		*tokens; //linked list with tokens
	t_exec 		*exec;
	bool		lex_error;
	bool		parse_error;
	bool		exec_error;
	bool		exit_minishell;
}		t_data;




#endif
