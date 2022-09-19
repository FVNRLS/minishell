/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:35:33 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/19 13:22:46 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/minishell.h"

void	check_leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_data 	data;
	(void) argc;
	(void) argv;
	signal(SIGINT, SIG_IGN); // Ctrl C dont work now
	//g_exit_code = 0;
	init_shell_env(&data, envp);
	while (data.exit_minishell == false)
	{
		track_history(&data);
		lex_input(&data);
		if (data.lex_error == false)
		{
			parse_tokens(&data);
			if (data.parse_error == false)
			{
				print_tokens(&data);
				exec_commands(&data);
			}
			//close(data.fd_in);
			//close(data.fd_out);
		}
		free_tokens(&data);
//		check_leaks();
	}
	free_all_ressources(&data);
	//atexit(check_leaks);

	return (EXIT_SUCCESS);
}



