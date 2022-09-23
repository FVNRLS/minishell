/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_extractor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:34:00 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/23 19:11:18 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO: cont here - try to exec!

#include "../../../incl/minishell.h"

/*
	Checks the existing command for validity by trying to combine it with
 	different paths and checking them for existence with the access() function.
	If access() returns 0, it means that the path exists and can be returned.
*/
//static char	*assign_path(char **paths, char *cmd)
//{
//	int		i;
//	char	*path;
//	char	*path_with_slash;
//	char	*slash;
//
//	path = NULL;
//	path_with_slash = NULL;
//	slash = ft_strdup("/");
//	i = 0;
//	while (paths[i] != NULL)
//	{
//		path_with_slash = ft_strjoin(paths[i], slash);
//		path = ft_strjoin(path_with_slash, cmd);
//		free(path_with_slash);
//		if (access(path, F_OK) == 0)
//			break ;
//		free(path);
//		path = NULL;
//		i++;
//	}
//	free(slash);
//	slash = NULL;
//	return (path);
//}

/*
	Finds and returns all paths of the env var. 'PATH', separated by
 	the delimiter ':';
 	Iterate through all available env vars and compare the first 5 character.
 	If the first 5 chars are 'PATH=' - this env index contains the paths.
 	Return the pointer to 6th position (char.) of the env var
 	(the arg. 'PATH=' doesnt belong to the actual paths).
 	If no env with 'PATH=' specified, set the path to CWD.
*/
static char	**get_all_paths(t_data *data)
{
	t_envp	*envp;
	char	*paths;
	char 	**split_paths;

	envp = data->envp;
	paths = NULL;
	while (envp != NULL)
	{
		if (ft_strcmp("PATH", envp->key) == 0)
		{
			paths = envp->val;
			break;
		}
		envp = envp->next;
	}
	if (!paths)
		return (NULL);
	split_paths = ft_split(paths, DOUBLE_DOT);
	if (!split_paths)
	{
		perror(NULL);
		data->exec_error = true;
		return (NULL);
	}
	return (split_paths);
}

/*
	Gets a full path for the given command, received from argv.
*/
char	*get_cmd(t_data *data, t_token *token)
{
	char 	**content;
	char 	**all_paths;
	char	*cmd;
	char	*cmd_path;

	cmd_path = NULL;
	content = ft_split(token->content, SPACE);
	if (!content)
	{
		perror(NULL);
		data->exec_error = true;
		return (NULL);
	}
	cmd = content[0];
	all_paths = get_all_paths(data);
	if (data->exec_error == false)
	{
//		cmd_path = assign_path(all_paths, cmd);
		ft_cleansplit(all_paths);
	}
	ft_cleansplit(content);
	return (cmd_path);
}