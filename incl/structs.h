/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:53:01 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/08 13:13:42 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>


#ifndef STRUCTS_H
# define STRUCTS_H

# define NUM_BUILTINS	7

typedef struct s_tokens //linked tokens
{
	char			*name;
	int				flag; //?
	struct s_tokens	*next;
}		t_tokens;

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
}		t_builtins;


typedef struct s_data
{
	t_builtins	*builtins;
	char 		*lst_cmd;
	t_envp		*envp; // linked list - contains all environments
	t_tokens	*tokens; //linked list with tokens

	bool		error;
	bool		exit_minishell;
	int			status; //catch signal exit codes and process execution
}		t_data;




#endif
