/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:52:40 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/13 13:06:10 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <termios.h>

# include "builtins.h"
# include "errors.h"
# include "structs.h"
# include "tools.h"

# ifndef SIZE_MAX
#  define SIZE_MAX __SIZE_MAX__
# endif

# define SPACE				' '
# define SINGLE_QUOTE		'\''
# define DOUBLE_QUOTE		'\"'
# define DOLLAR				'$'
# define REDIRECT_IN		'<'
# define REDIRECT_OUT		'>'
# define PIPE				'|'

//TOKEN FLAGS:
//if TOKEN == WORD/FIELD/EXPANDABLE_FIELD -> expand!
# define T_WORD				1 // also commands: eg. echo, @, .
# define T_REDIRECT_IN		2 // file <
# define T_REDIRECT_OUT		3 // file >
# define T_APPEND_IN		4 // file >>
# define T_HEREDOC			5 // << file
# define T_PIPE				6 // |

int 	g_exit_code;

//INITIALIZER:
void	init_shell_env(t_data *data, char **envp);
void	init_envp(t_data *data, char **envp);
void	init_builtin_names(t_data *data);
void	init_builtin_functions(t_data *data);

//DESTRUCTOR:
void	free_tokens(t_data *data);
void	free_envp(t_data *data);
void	free_builtins(t_data *data);
void	free_all_ressources(t_data *data);
void	exit_with_free(t_data *data);

//HISTORY TRACKER
void	track_history(t_data *data);

//LEXER:
void	lex_input(t_data *data);
void	create_tokens(t_data *data, t_lex *lex);
bool	check_sep(t_data *data, char c);
void	add_token(t_data *data, t_lex *lex);
void	join_tokens(t_data *data);
void	handle_redirections(t_data *data, t_lex *lex);
void	handle_words(t_data *data, t_lex *lex);
void	handle_single_quotes(t_data *data, t_lex *lex);
void	handle_double_quotes(t_data *data, t_lex *lex);
bool	find_redirections(t_lex *lex);
void	handle_expansion(t_data *data, t_lex *lex);
bool	check_open_quotes(t_data *data, t_lex *lex);
void 	stop_lexing(t_data *data, t_lex *lex);


//TODO: delete before submission!
void	print_tokens(t_data *data);


#endif
