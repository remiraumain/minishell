/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:40:01 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/11 15:21:45 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_global_data	*data;

	(void)argc;
	(void)argv;
	data = init_global_data(envp);
	if (!data)
		return (0);
	set_minishlvl(data->envp);
	while (1)
	{
		if (g_sig != -29)
			g_sig = 0;
		set_parent_signals(data);
		input = readline("minishell> ");
		handle_signal(data);
		if (!input)
			return (clean_exit(data));
		process_input(input, data);
		free(input);
		data->line_count++;
	}
	return (data->status);
}
