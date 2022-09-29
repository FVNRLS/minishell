/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:31:55 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/28 17:46:59 by jjesberg         ###   ########.fr       */
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
t_envp	*ft_new_envp(char *key, char *value);
t_token	*ft_new_token(char *content, int flag);
size_t	ft_strlen(const char *s);
char	*ft_strdup(char *s1);
int		ft_strcmp(char *s1, char *s2);
char	*ft_join_char(char *buf, char c);
char	*ft_strtrim(char *str, char delim);
void	ft_add_token_back(t_token **lst, t_token *new);
char	*ft_itoa(int n);
char	*ft_strjoin(char *buf, char *tmp);
char	**ft_split(char const *s, char c);
void	ft_cleansplit(char **split);
int		ft_get_builtin(t_data *data);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
t_envp	*ft_getenvp(t_data *data, char *find);
int		ft_isnumber(char *s, long long sum, int i);
int		ft_isdigit(int c);
int		ft_splitlen(char **s);
int		ft_haschar(char *s, char c);
int		ft_isprint(int c);
void	ft_del_first_token(t_data **data);
int 	ft_get_num_cmds(t_data *data);
int		ft_isalpha(int c);


//for debuging
int		print_list(t_token *data);

#endif
