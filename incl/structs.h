/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:53:01 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/17 21:57:44 by jjesberg         ###   ########.fr       */
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
	int			pipe;
	void		*ptr;
	int			id;
	char		**command_pipe;
	char		*cmd_now;
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


typedef struct s_data
{
	t_builtins	*builtins;
	char 		*input;
	char		*sep;
	int 		*redir;
	int 		fd_in;
	int 		fd_out;
	t_envp		*envp; // linked list - contains all environments
	t_token		*tokens; //linked list with tokens
	bool		lex_error;
	bool		parse_error;
	bool		exec_error;
	bool		exit_minishell;
	int			status; //catch signal exit codes and process execution
}		t_data;




#endif
