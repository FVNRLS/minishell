/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_creater.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:38:03 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/01 11:47:57 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

static int count_hdoc_files(t_data *data)
{
	t_token	*tmp;
	int 	i;

	tmp = data->tokens;
	if (!tmp)
		return (0);
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->flag == T_HEREDOC)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static void	create_hdoc(t_data *data)
{
	char 	*path;
	char 	*index;
	char 	*hdoc;

	path = ft_strdup("/tmp/");
	index = ft_itoa(data->fd->hdoc_index);
	hdoc = ft_strjoin(path, index);
	free(index);
	index = NULL;
	data->fd->hdoc[data->fd->hdoc_index] = ft_strdup(hdoc);
	data->fd->in = open(hdoc, O_CREAT | O_RDWR | O_TRUNC, RIGHTS);
	if (data->fd->in < 0 || access(hdoc, F_OK) < 0 || access(hdoc, R_OK) < 0)
	{
		perror(NULL);
		data->parse_error = true;
	}
	free(hdoc);
	hdoc = NULL;
}

static void read_from_stdin(t_data *data, t_token *token)
{
	char	*input;
	bool	lim_found;

	lim_found = false;
	while (lim_found == false)
	{
		input = readline("> ");
		if (!input)
			break ;
		if (ft_strcmp(input, token->content) == 0)
			lim_found = true;
		else
		{
			input = ft_strjoin(input, "\n");
			if (write(data->fd->in, input, ft_strlen(input)) < 0)
			{
				perror(token->content);
				data->parse_error = true;
				exit(EXIT_FAILURE);
			}
		}
		free(input);
		input = NULL;
	}
	exit(EXIT_SUCCESS);
}

static void	read_to_hdoc(t_data *data, t_token *token)
{
	int	status;

	data->pid = fork();
	if (data->pid < 0)
		perror(NULL);
	else if (data->pid == 0)
		read_from_stdin(data, token);
	waitpid(data->pid, &status, 0);
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		if (status != 0)
		{
			data->parse_error = true;
			g_exit_code = EXIT_FAILURE;
		}
	}
}

void	parse_hdocs(t_data *data)
{
	t_token	*tmp;
	int 	cnt;

	cnt = count_hdoc_files(data);
	if (cnt == 0)
		return;
	else
	{
		data->fd->hdoc = malloc(sizeof(char *) * (cnt + 1));
		data->fd->hdoc[cnt] = NULL;
	}
	tmp = data->tokens;
	while (tmp != NULL)
	{
		if (tmp->flag == T_HEREDOC)
		{
			create_hdoc(data);
			read_to_hdoc(data, tmp);
			if (data->parse_error == true)
			{
				destroy_hdocs(data);
				return ;
			}
			close(data->fd->in);
			data->fd->in = 0;
			data->fd->hdoc_index++;
		}
		tmp = tmp->next;
	}
}