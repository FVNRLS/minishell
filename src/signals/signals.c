/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:10:29 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/11 22:15:07 by rmazurit         ###   ########.fr       */
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
	rl_replace_line("", 0);
}

static void	catch_backslash(int sig_num)
{
	(void)sig_num;
	ioctl(STDIN_FILENO, TIOCSTI, "");
	rl_on_new_line();
	rl_replace_line("", 0);
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
