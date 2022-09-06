/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:53:01 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/06 19:56:18 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>


#ifndef STRUCTS_H
# define STRUCTS_H

//a t_llist node contains 2 elements: key, value

//TOKENS:
# define WORD				1 // also commands: eg. echo, @, .
# define FIELD				2 // single quotes
# define EXPANDABLE_FIELD	3 // double quotes to split (?)
# define REDIRECT_IN		4 // file <
# define REDIRECT_OUT		5 // file >
# define APPEND_IN			6 // file >
# define REDIRECT_FROM_SRC	7 // read from here_doc file
# define PIPE				8 // |

//if TOKEN == WORD/FIELD/EXPANDABLE_FIELD -> expand!


typedef struct s_tokens //linked tokens
{
	char			*name;
	int				flag; //?
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_envp
{
	char 				*env_name; //eg. name f the variable
	void 				*env_val; //eg. path or value of the variable
	struct s_envp	*next;
} t_envp;

typedef struct s_data
{
	char		builtins_names[7]; //strcmp the tokens with reserved words and if match - call the builtins on the sam index
	char 		builtins_functions[7]; // builtin functions
	t_envp		*envps_list; // linked list - contains all environments
	t_tokens	*tokens; //linked list with tokens

	bool		exit_minishell;
	int			status; //catch signal exit codes and process execution
} t_data;




#endif
