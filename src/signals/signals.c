/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 17:10:29 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/29 21:26:04 by jjesberg         ###   ########.fr       */
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