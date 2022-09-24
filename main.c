/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:35:33 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/24 16:22:59 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/minishell.h"

void	check_leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **env)
{
	t_data 	data;
	(void) argc;
	(void) argv;
	g_exit_code = 0;
	init_shell_env(&data, env);
	while (data.exit_minishell == false)
	{
		track_history(&data);
		catch_signals(&data);
		lex_input(&data);
		if (data.lex_error == false)
		{
			parse_tokens(&data);
			if (data.parse_error == false)
			{
//				exec_commands(&data);
				exec_bash_commands(&data);
				print_tokens(&data);
			}
		}
		free_tokens(&data);
		destroy_hdocs(&data); //run after total exec
//		check_leaks();
	}
	free_all_ressources(&data);
	atexit(check_leaks);
	return (EXIT_SUCCESS);
}



