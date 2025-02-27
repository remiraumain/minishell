/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:40:01 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/26 18:46:08 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else
	{
		execute_cmds(cmds, data->envp);
		free_cmd_list(cmds);
	}
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
	data->status = 0;
	while (1)
	{
		data->envp = envp;
		input = readline("minishell> ");
		if (!input)
		{
			free(data);
			rl_clear_history();
			return (0);
		}
		process_input(input, data);
		free(input);
	}
	rl_clear_history();
	return (0);
}
