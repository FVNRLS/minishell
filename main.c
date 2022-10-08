/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmazurit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:35:33 by rmazurit          #+#    #+#             */
/*   Updated: 2022/10/08 19:49:35 by rmazurit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./incl/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void) argc;
	(void) argv;
	init_shell_env(&data, env);
	while (data.exit_minishell == false)
	{
		ft_signals(MAIN_PROCESS);
		track_history(&data);
		lex_input(&data);
//		print_tokens(&data);
		if (data.lex_error == false)
		{
			parse_tokens(&data);
			if (data.parse_error == false)
				execute_tokens(&data);
		}
		free_tokens(&data);
	}
	free_all_ressources(&data);
	return (g_exit_code);
}
