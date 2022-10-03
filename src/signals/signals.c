/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:10:29 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/04 00:06:38 by jjesberg         ###   ########.fr       */
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

	tcgetattr(STDIN_FILENO, &saved);
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	tcgetattr(STDIN_FILENO, &att);
    att.c_lflag &= ~ ECHOCTL;
    tcsetattr(STDIN_FILENO, 0, &att);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

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
	t_envp	*tmp;

	tmp = ft_getenvp(data, "?_PID");
	signal(SIGUSR1, handler);
	if (flag == 0)
		return (signal(SIGINT, ctrl_c));
	if (flag == 1)
	{
		signal(SIGINT, catch_herd);
		if (catch_herd(99) == 42)
		{
			kill(ft_atoi(tmp->val), SIGUSR1);
			exit(1);
		}
		return (2);
	}
	return (0);
}
