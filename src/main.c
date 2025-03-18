/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:40:01 by rraumain          #+#    #+#             */
/*   Updated: 2025/03/18 12:53:09 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

static void	process_input(char *input, t_global_data *data)
{
	t_token	*tokens;
	t_cmd	*cmds;

	if (*input)
		add_history(input);
	tokens = lexer(input, data);
	if (!tokens)
		return ;
	cmds = parse_line(tokens);
	free_token_list(tokens);
	if (!cmds)
		return ;
	else if (cmds && !g_sig)
	{
		execute_cmds(cmds, data);
		free_cmd_list(cmds);
	}
	else
		free_cmd_list(cmds);
}

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_global_data	*data;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_global_data));
	if (!data)
		return (0);
	data->envp = init_env(envp);
	if (!data->envp)
		return (0);
	data->status = 0;
	while (1)
	{
		set_parent_signals();
		input = readline("minishell> ");
		g_sig = 0;
		if (!input)
		{
			clear_env(data->envp);
			free(data);
			rl_clear_history();
			return (0);
		}
		process_input(input, data);
		free(input);
	}
}
