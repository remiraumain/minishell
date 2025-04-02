/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:40:01 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/01 18:51:05 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

static void	process_input(char *input, t_global_data *data)
{
	t_token	*tokens;
	t_cmd	*cmds;
	int		i;

	i = -1;
	if (*input)
		add_history(input);
	while (input[++i] != '\0')
	{
		if (input[0] == '|' || (input[i] == '|' && input[i + 1] == '\0'))
		{
			ft_putstr_fd("bash: syntax error near unexpected token '|'\n", 2);
			data->status = 2;
			return ;
		}
	}
	tokens = lexer(input, data);
	if (!tokens)
		return ;
	cmds = parse_line(tokens);
	free_token_list(tokens);
	if (!cmds)
		return ;
	execute_cmds(cmds, data);
	free_cmd_list(cmds);
}



/*
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
	execute_cmds(cmds, data);
	free_cmd_list(cmds);
}*/


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
	{
		free (data);
		return (0);
	}
	data->status = 0;
	while (1)
	{
		if (g_sig != -29)
			g_sig = 0;
		set_parent_signals();
		input = readline("minishell> ");
		if (g_sig)
		{
			data->status = 130;
			g_sig = 0;
		}
		if (!input)
		{
			clear_env(data->envp);
			free(data);
			rl_clear_history();
			return (0);// return (data->status);
		}
		process_input(input, data);
		free(input);
	}
	return (data->status);
}
