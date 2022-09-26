/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:42:25 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/26 00:25:36 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"
# include <errno.h>
# include <unistd.h>
# include <sys/types.h>

//utils
char	*make_key(char *s, int *i);
void	true_env(t_data *data);

/*
print data.envp.key & data.envp.key till envp->next == NULL
if cmd:
env | echo n 
cmd env will be ignored atm
*/
int	env(t_data *data);

/*
data->envp->val = start path? or updated? 
or cd() should update (data.val//data.val.next) 
or an other fnct should do?
export & unset env ?
ARGS = ".."  & any path "Names"
if error occurs return 1
*/
int cd(t_data *data);

/*
print the pathname of current working directory
if error occurs return 1
*/
int pwd(void);

/*
flag echo -n dont work atm
*/
int	echo(t_data *data);

/*
not finished yet
*/
int	export(t_data *data);

/*
exit minishell should be fine
pls test exit against bugs
*/
int	mini_exit(t_data *data);

/*
not finished yet
*/
int	unset(t_data *data);

#endif
