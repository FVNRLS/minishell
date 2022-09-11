/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:35:33 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/11 16:21:05 by rmazurit         ###   ########.fr       */
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
	g_exit_code = 0;
	init_shell_env(&data, envp);
	while (data.exit_minishell == false)
	{
		track_history(&data);
		lex_input(&data);
		if (data.lex_error == false)
		{
			print_tokens(&data);
	//		parser();
//			exec();
		}
		free_tokens(&data);
		check_leaks();
	}
	free_all_ressources(&data);
	atexit(check_leaks);

	return (EXIT_SUCCESS);
}



