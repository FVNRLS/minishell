/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:35:33 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/15 11:54:46 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/*
	Imitated Bash without support of special characters (eg. ';' '\', wildcards)
	
	Structure:
	First initialization.
		Running minishell as while loop with repetitive procedure:
			1) Catch signals
			2) Prompt and save user input. Add the input to the history.
			3) Lexical analysis of the input + splitting into tokens.
			4) Parse the created tokens list.
			5) Execute tokens commands with redirections and pipes
	In the all allocated files, linked lists and arrays are freed.

*/
int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc != 1)
	{
		printf("minishell: %s: No such file or directory\n", argv[1]);
		return (EXIT_FAILURE);
	}
	(void) argv;
	init_shell_env(&data, env);
	while (data.exit_minishell == false)
	{
		ft_signals(MAIN_PROCESS);
		track_history(&data);
		lex_input(&data);
		if (data.lex_error == false)
		{
//			print_tokens(&data);
			parse_tokens(&data);
			if (data.parse_error == false)
				execute_tokens(&data);
		}
		free_tokens(&data);
	}
	free_all_ressources(&data);
	return (g_exit_code);
}
