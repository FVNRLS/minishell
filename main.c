/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:35:33 by rmazurit          #+#    #+#             */
/*   Updated: 2022/09/29 21:36:20 by jjesberg         ###   ########.fr       */
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
	init_shell_env(&data, env);
	while (data.exit_minishell == false)
	{
		signal(SIGINT, catch_signals);
		signal(SIGQUIT, SIG_IGN);
		track_history(&data);
		lex_input(&data);
		if (data.lex_error == false)
		{
			parse_tokens(&data);
			print_tokens(&data);
			if (data.parse_error == false)
				execute_tokens(&data);
		}
		free_tokens(&data);
//		check_leaks();
	}
	free_all_ressources(&data);
	return (EXIT_SUCCESS);
}
