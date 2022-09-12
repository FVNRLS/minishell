/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:31:55 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/10 20:27:06 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

#ifndef TOOLS_H
# define TOOLS_H

//NODES:
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_add_envp_back(t_envp **lst, t_envp *new);
void	ft_lstclear(t_envp **lst);
void	ft_lstdelone(t_envp *lst);
t_envp	*ft_new_envp(char *key, char *value);
t_token	*ft_new_token(char *content, int flag);
int		ft_lstsize(t_envp *lst);
size_t	ft_strlen(const char *s);
char	*ft_strdup(char *s1);
int		ft_strcmp(char *s1, char *s2);
char	*ft_join_char(char *buf, char c);
char	*ft_strtrim(char *str, char delim);
void	ft_add_token_back(t_token **lst, t_token *new);
char	*ft_itoa(int n);
char	*ft_strjoin(char *buf, char *tmp);
char	**ft_split(char const *s, char c);

#endif
