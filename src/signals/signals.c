/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:10:29 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/30 19:24:15 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void catch_signals(int sig_num)
{
	struct termios att;
	struct termios saved;

	tcgetattr(STDIN_FILENO, &saved);
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	tcgetattr(STDIN_FILENO, &att);
    att.c_lflag &= ~ ECHOCTL;
    tcsetattr(STDIN_FILENO, 0, &att);
	if (sig_num == SIGINT)
	{
		g_exit_code = 0;
		if (ioctl(STDIN_FILENO, TIOCSTI, "\n"))
			g_exit_code = printf("ERROR\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	
}

static void	catch_herd(int sig_num)
{
	write(1, ">\n", 2);
	if (sig_num == 2)
		exit(1);
}

void	ft_signals(int flag)
{
	if (flag == 0)
	{
		signal(SIGINT, catch_signals);
		signal(SIGQUIT, SIG_IGN);
	}
	if (flag == 1)
	{
		signal(SIGINT, catch_herd);
	}
}
