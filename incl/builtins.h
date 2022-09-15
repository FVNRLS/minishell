/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:42:25 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/14 11:06:11 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"
# include <errno.h>
# include <unistd.h>
# include <sys/types.h>

/*
error management of builtins uses perror / errno messages
ARGS:	m = message of ur choice
		error = errno 
if errno is unset choose val for errno only occurs when no "real" error happens
        1 Operation not permitted
        2 No such file or directory
        3 No such process
        4 Interrupted system call
        5 Input/output error
		... look man errno | man perror gl
*/
int error(char *m, int error);

/*
print data.envp.key & data.envp.key till envp->next == NULL
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
int cd(char *val);

/*
print the pathname of current working directory
if error occurs return 1
*/
int pwd(void);

int	echo(char *s);
int	export(char *s);
int	mini_exit(char *s);
int	unset(char *s);

#endif
