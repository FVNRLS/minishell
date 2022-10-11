/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_extractor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:34:00 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/09 10:39:09 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*
	Checks the existing command for validity by trying to combine it with
 	different paths and checking them for existence with the access() function.
	If access() returns 0, it means that the path exists and can be returned.
*/
static char	*assign_path(char **paths, char *cmd)
{
	int		i;
	char	*path;
	char	*path_with_slash;
	char	*slash;

	path = NULL;
	path_with_slash = NULL;
	slash = ft_strdup("/");
	i = 0;
	while (paths[i] != NULL)
	{
		path = ft_strdup(paths[i]);
		path_with_slash = ft_strjoin(path, slash);
		path = ft_strjoin(path_with_slash, cmd);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	free(slash);
	return (path);
}

/*
	Finds and returns all paths of the env var. 'PATH', separated by
 	the delimiter ':';
 	Iterates through all available env vars and compares the env key.
 	If env. list contains var. PATH - returns its value.
 	If no env with 'PATH' specified, set the path to CWD.
*/
static char	**get_valid_paths(t_data *data)
{
	t_envp	*envp;
	char	*path;
	char	**valid_paths;

	envp = data->envp;
	path = NULL;
	while (envp != NULL)
	{
		if (ft_strcmp("PATH", envp->key) == 0)
		{
			path = envp->val;
			break ;
		}
		envp = envp->next;
	}
	if (!path)
		path = ft_strdup("./");
	valid_paths = ft_split(path, ':');
	if (!valid_paths)
		return (NULL);
	if (ft_strcmp(path, "./") == 0)
		free(path);
	return (valid_paths);
}

/*
	Gets a full path to the given command (binary or executable).
*/
char	*get_cmd_path(t_data *data)
{
	char	*cmd;
	char	**valid_paths;
	char	*cmd_path;

	cmd = data->exec->cmd[0];
	valid_paths = get_valid_paths(data);
	if (!valid_paths)
	{
		perror(NULL);
		data->exec_error = true;
		return (NULL);
	}
	cmd_path = assign_path(valid_paths, cmd);
	ft_cleansplit(valid_paths);
	return (cmd_path);
}

char	**get_cmd(t_data *data, t_token *token)
{
	char	**cmd;

	cmd = ft_split(token->content, SPACE);
	if (!cmd)
	{
		perror(NULL);
		data->exec_error = true;
		return (NULL);
	}
	return (cmd);
}

char	**extract_cmd_from_path(t_data *data, t_token *token)
{
	char	**input;
	char	**path;
	char	*cmd;

	input = ft_split(token->content, SPACE);
	if (!input)
		return (NULL);
	path = ft_split(input[0], SLASH);
	if (!path)
		return (NULL);
	data->exec->path = ft_strdup(input[0]);
	if (!data->exec->path)
		return (NULL);
	cmd = ft_strdup(path[ft_splitlen(path) - 1]);
	if (!cmd)
		return (NULL);
	ft_cleansplit(path);
	path = NULL;
	free(input[0]);
	input[0] = cmd;
	return (input);
}
