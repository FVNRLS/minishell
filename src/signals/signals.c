/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <j.jesberger@heilbronn.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:10:29 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/13 13:46:22 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*
Control C = New prompt

att.c_lflag &= ~ECHOCTL will comntrol all Cntrl prints like C^ D^ etc.
cause echo is silenced in some way

and simulate a new readline
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
	rl_replace_line("", 0);
}

/*
will wait for Ctrl+\ signal
and simulate a readline
will not quit the process
*/
static void	catch_backslash(int sig_num)
{
	(void)sig_num;
	ioctl(STDIN_FILENO, TIOCSTI, "");
	rl_on_new_line();
	rl_replace_line("", 0);
}

/*
just a static int which remember the last sig

mode 99:
returns the value of the last sig when using sig_num with value 99

mode 2:
will save val 42 cause he caught a signal (sig_num = 2)

mode n: (any other number)
will delete the static save and returns -1
*/
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
signal handler for main process and its pid's

Ctrl+C : new prompt
Ctrl+D : exit process
Ctrl+Z : interupt process
Ctrl+\ : does nothing

if signal comes from child process
a handler (*) will save status of last signal

(*)
look at:
static int	catch_herd(int sig_num)
*/
void	ft_signals(int flag)
{
	if (flag == MAIN_PROCESS)
	{
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, (void *)catch_backslash);
	}
	else if (flag == CHILD_PROCESS)
	{
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, &catch_backslash);
		signal(SIGINT, (void *)catch_herd);
		if (catch_herd(99) == 42)
			exit(TERMINATED_BY_CTRL_C);
	}
}
