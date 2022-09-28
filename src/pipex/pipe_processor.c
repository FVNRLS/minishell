/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_processor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 19:30:37 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/28 19:40:34 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int create_fork(t_data *data)
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

static int create_pipe(t_data *data)
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
	Replaces stdin with infile and passes the output via to the first command
 	via the pipe.
	If the command fails - terminates the program.
	To do this, first open the pipe and create a fork with (parent + child).
	The command is always executed on the child and the parent always waits
 	until the child is ready to pass the output to next command via the pipe.
 	If the status is not 0, it means the command failed -> exit the program!
	The unused ends of the pipe are closed and the output of the command becomes
 	the new input for the next command.

 	Exec.:
	<Child process>
	Takes the input from the input file (be it her_doc or the infile) and passes
	it as output to the first end of the opened pipe.

 	Closes unused pipe end before passing and used - after passing.
 	Closes the duplicated fd after using.
	Executes the command with execve().
	If the command fails - prints the appropriate error message and exits the
 	child process with status != 0
 	--> will be handled from parent process as signal to exit the program.
*/
void	pipe_first_cmd(t_data *data, t_token *token)
{
	extract_cmd_and_path(data, token);
	if (data->exec_error == true)
		return ;
	if (create_pipe(data) < 0)
		return ;
	if (create_fork(data) < 0)
		return ;
	else if (data->pid == 0)
		exec_first_cmd(data, token);
	catch_exit_code(data);
	free_cmd_and_path(data);

	close(data->pipe[1]);
	dup2(data->pipe[0], STDIN_FILENO); //don't understand why!!!
	close(data->pipe[0]);
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
void	pipe_inter_cmd(t_data *data, t_token *token)
{
	extract_cmd_and_path(data, token);
	if (data->exec_error == true)
		return ;
	if (create_pipe(data) < 0)
		return ;
	if (create_fork(data) < 0)
		return ;
	else if (data->pid == 0)
		exec_inter_cmd(data, token);
	catch_exit_code(data);
	free_cmd_and_path(data);

	close(data->pipe[1]);
	dup2(data->pipe[0], STDIN_FILENO);
	close(data->pipe[0]);
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
void	pipe_last_cmd(t_data *data, t_token *token)
{
	extract_cmd_and_path(data, token);
	if (data->exec_error == true)
		return ;
	if (create_pipe(data) < 0)
		return ;
	if (create_fork(data) < 0)
		return ;
	else if (data->pid == 0)
		exec_last_cmd(data, token);
	catch_exit_code(data);
	free_cmd_and_path(data);
}
