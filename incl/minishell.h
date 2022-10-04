/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:52:40 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/04 15:09:21 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <termios.h>
# include <sys/ioctl.h>

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
# define T_WORD				1 // also commands: eg. echo, @, .
# define T_REDIRECT_IN		2 // file <
# define T_REDIRECT_OUT		3 // file >
# define T_APPEND			4 // file >>
# define T_HEREDOC			5 // << file
# define T_PIPE				6 // |

static int 	g_exit_code = 0;

//INITIALIZER:
void	init_shell_env(t_data *data, char **envp);
void	init_envp(t_data *data, char **envp);
void	init_builtin_names(t_data *data);
void	init_builtin_functions(t_data *data);
void 	init_fd(t_data *data);
void	init_exec(t_data *data);


//DESTRUCTOR:
void	free_tokens(t_data *data);
void	free_envp(t_data *data);
void	free_builtins(t_data *data);
void	free_all_ressources(t_data *data);
void	exit_with_free(t_data *data);
void 	destroy_hdocs(t_data *data);
void	free_cmd_and_path(t_data *data);

//HISTORY TRACKER
void	track_history(t_data *data);

//LEXER:
void	lex_input(t_data *data);
void	create_tokens(t_data *data, t_lex *lex);
bool	check_sep(t_data *data, char c);
void	add_token(t_data *data, t_lex *lex);
void	handle_redirections(t_data *data, t_lex *lex);
void	handle_words(t_data *data, t_lex *lex);
void	handle_single_quotes(t_data *data, t_lex *lex);
void	handle_double_quotes(t_data *data, t_lex *lex);
bool	find_redirections(t_lex *lex);
void	handle_expansion(t_data *data, t_lex *lex);
bool	check_open_quotes(t_data *data, t_lex *lex);
void 	stop_lexing(t_data *data, t_lex *lex);
void	expand_last_return(t_data *data, t_lex *lex);
void	try_expansion(t_data *data, t_lex *lex);
void	expand_parameter(t_data *data, t_lex *lex);
void 	handle_multiple_dollars(t_data *data, t_lex *lex);
void	handle_one_dollar(t_data *data, t_lex *lex);

//PARSER
void	parse_tokens(t_data *data);
void	check_multiple_pipes(t_data *data);
void	refactor_join_flags(t_data *data);
void	merge_joinable_tokens(t_data *data);
void	merge_words(t_data *data);
void	merge_redirections(t_data *data);
bool	check_redir(t_data *data, int flag);
bool 	check_redir_syntax_error(t_data *data, t_token *token);
void	check_fd_access(t_data *data, t_token *token);
void	check_create_error(t_data *data, t_token *token);
void	resolve_redirections(t_data *data);
void	parse_hdocs(t_data *data);
void	redirect_in(t_data *data, t_token *token);
void	redirect_from_hdoc(t_data *data);
void	redirect_out(t_data *data, t_token *token);
void	append(t_data *data, t_token *token);
void	close_unused_fd_in(t_data *data);
void 	close_unused_fd_out(t_data *data);
void 	close_fds_in_out(t_data *data);

//EXECUTER
void	execute_tokens(t_data *data);
void	extract_cmd_and_path(t_data *data, t_token *token);

//PIPEX
void	pipe_transitory_cmd(t_data *data);
void	pipe_last_cmd(t_data *data);
void	exec_transitory_builtin(t_data *data, int builtin);
void	exec_last_builtin(t_data *data, int builtin);
void	exec_transitory_cmd(t_data *data);
void	exec_last_cmd(t_data *data);
void 	exec_bash_cmd(t_data *data);

//SIGNALS
int	ft_signals(int flag, t_data *data);

//TODO: delete before submission!
void	print_tokens(t_data *data);
void	check_leaks(void);

#endif
