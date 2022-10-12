/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_processor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <rmazurit@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 19:30:37 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/12 10:37:45 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	catch_exit_code(t_data *data)
{
	int	status;

	status = g_exit_code;
	waitpid(data->pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
}

static int	create_fork(t_data *data)
{
	data->pid = fork();
	if (data->pid < 0)
	{
		perror(NULL);
		free_cmd_and_path(data);
		return (-1);
	}
	return (0);
}

static int	create_pipe(t_data *data)
{
	if (pipe(data->pipe) < 0)
	{
		perror(NULL);
		free_cmd_and_path(data);
		return (-1);
	}
	return (0);
}

/*
	Takes the output of the previous command and transfers it to next command.
	Basic behaviour is the same as in pipe_infile().

 	Exec.:
	<Child process>
	Takes the output from the previous command via the last end of the pipe and
 	passes it to the next end of the pipe.

	Closes unused pipe end before passing and used - after passing.
  	Closes the duplicated fd after using.
	Executes the command with execve().
	If the command fails - prints the appropriate error message and exits the
 	child process with status != 0
 	--> will be handled from parent process as signal to exit the program.
*/
void	pipe_transitory_cmd(t_data *data)
{
	int	builtin;

	if (create_pipe(data) < 0)
		return ;
	if (data->exec->no_cmd == true || data->parse_error == true)
	{
		redirect_stdin_to_pipe(data);
		return ;
	}
	builtin = ft_get_builtin(data);
	if (builtin >= 0)
		exec_transitory_builtin(data, builtin);
	else
	{
		if (create_fork(data) < 0)
			return ;
		if (data->pid == 0)
		{
			redirect_transitory_cmd(data);
			exec_bash_cmd(data);
		}
		redirect_stdin_to_pipe(data);
	}
}

/*
	Takes the output of the previous command and writes it to outfile.
	Basic behaviour is the same as in pipe_infile(), with only one difference:
 	here is no pipe needed anymore, because the output can just be duplicated
 	to outfile with dup2().

 	Exec.:
 	<Child process>
	Takes the output from the last command and passes it as output to outfile.
	Executes the command with execve().

	Closes the duplicated fd after using.
	If the command fails - prints the appropriate error message and exits the
 	child process with status != 0
 	--> will be handled from parent process as signal to exit the program.
*/
void	pipe_last_cmd(t_data *data)
{
	int	builtin;

	if (data->exec->no_cmd == true || data->parse_error == true)
	{
		reset_stdin_stdout(data);
		if (data->parse_error == true)
			g_exit_code = EXIT_FAILURE;
		return ;
	}
	builtin = ft_get_builtin(data);
	if (builtin >= 0)
		exec_last_builtin(data, builtin);
	else
	{
		signal(SIGINT, SIG_IGN);
		if (create_fork(data) < 0)
			return ;
		if (data->pid == 0)
		{
			redirect_last_cmd(data);
			exec_bash_cmd(data);
		}
	}
	reset_stdin_stdout(data);
}
