/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:52:40 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/07 12:35:46 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "stdlib.h"
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <termios.h>

# include "structs.h"
# include "errors.h"
# include "tools.h"

//TOKEN FLAGS:
//if TOKEN == WORD/FIELD/EXPANDABLE_FIELD -> expand!
# define WORD				1 // also commands: eg. echo, @, .
# define FIELD				2 // single quotes
# define EXPANDABLE_FIELD	3 // double quotes to split (?)
# define REDIRECT_IN		4 // file <
# define REDIRECT_OUT		5 // file >
# define APPEND_IN			6 // file >
# define REDIRECT_FROM_SRC	7 // read from here_doc file
# define PIPE				8 // |

//INITIALIZER:
void	init_shell_env(t_data *data, char **envp);
void	init_envp(t_data *data, char **envp);

//DESTRUCTOR:
void	free_all_ressources(t_data *data);

//PRINTER
void	print_envp(t_data *data);


#endif
