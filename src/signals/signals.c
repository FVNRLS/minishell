/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:10:29 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/05 17:10:32 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*
Control C = New prompt
*/
static void	ctrl_c(int sig_num)
{
	struct termios att;
	struct termios saved;

	(void)sig_num;
	tcgetattr(STDIN_FILENO, &saved);
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	tcgetattr(STDIN_FILENO, &att);
    att.c_lflag &= ~ ECHOCTL;
    tcsetattr(STDIN_FILENO, 0, &att);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

// we can share values between pid's here
static int	catch_herd(int sig_num) 
{
	static int save;

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

static void	handler(int sig)
{
	(void)sig;

	//printf("handler got the message:%i\n", sig);
	return ;
}

int	ft_signals(int flag, t_data *data)
{
	signal(SIGUSR1, handler);
	if (flag == 0)
	{
		signal(SIGINT, ctrl_c);
		return (0);
	}
	if (flag == 1)
	{
		
		signal(SIGINT, catch_herd);
		if (catch_herd(99) == 42)
			exit(1);
		return (2);
	}
	return (0);
}
