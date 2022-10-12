/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:42:25 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/12 11:14:22 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"
# include <errno.h>
# include <unistd.h>
# include <sys/types.h>

//export_utils.c /5
int		check_keys(char **s, int mode);
void	true_env(t_data *data);
int		check_string(t_data **data, int *i);
char	*make_key(char *s, int *i);

/*
export.c
-----------------------------------
export create a new key + optional a value
key=val
-----------------------------------
just export will print the whole envp's
*/
int		export(t_data *data);

/*
prints all Envp which has a value
*/
int		env(t_data *data);

/*
moving through the tree via cd "pathname"
*/
int		cd(t_data *data);
int		change_pwds(t_data *data);
int		fillempty(t_data *data, char **pwd_path, t_envp **pwd, t_envp **old);
int		home_path(char **s, t_data *data);

/*
prints current working directory
*/
int		pwd(void);

int		echo(t_data *data);
int		check_n(char *s);

/*
exit
*/
int		mini_exit(t_data *data);

/*
deletes envp entrys
*/
int		unset(t_data *data);
bool	flag_check(char *s, int mode);

#endif
