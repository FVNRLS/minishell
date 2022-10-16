/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:10:29 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/15 11:10:17 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*
Control C = New prompt
*/
static void	ctrl_c(int sig_num)
{
	struct termios	att;
	struct termios	saved;

	(void)sig_num;
	tcgetattr(STDIN_FILENO, &saved);
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	tcgetattr(STDIN_FILENO, &att);
	att.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &att);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
//	rl_replace_line("", 0);
}

static int	catch_herd(int sig_num)
{
	static int	save;

	if (sig_num == 99)
		return (save);
	if (sig_num == 2)
	{
		save = 42;
		return (1);
	}
	save = 0;
	return (-1);
}

/*
	Handles signals depending on the process running.

 	1) For main process:
 		--> ctrl-c signal is silenced and prints a newline.
 		--> ctrl-backslash shouldn't do anything
 	2) For child process:
 		--> all signals return to initial values.
 		--> ctrl-c should terminate the program on child process.
 		--> ctrl-backslash should cause SIGQUIT and terminate the program.
	3) For heredoc:
 		--> ctrl-c should terminate the opened child process with input prompt.
 		--> ctrl-backslash shouldn't do anything
*/
void	ft_signals(int flag)
{
	if (flag == MAIN_PROCESS)
	{
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (flag == CHILD_PROCESS)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
	else if (flag == HDOC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ctrl_c);
		signal(SIGINT, (void *)catch_herd);
		if (catch_herd(99) == 42)
			exit(TERMINATED_BY_CTRL_C);
	}
}
