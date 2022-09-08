/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:31:55 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/07 16:19:59 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

#ifndef TOOLS_H
# define TOOLS_H

//NODES:
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_add_back(t_envp **lst, t_envp *new);
void	ft_add_front(t_envp **lst, t_envp *new);
void	ft_lstclear(t_envp **lst);
void	ft_lstdelone(t_envp *lst);
t_envp	*ft_new_node(char *key, char *value);
int		ft_lstsize(t_envp *lst);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);

#endif
