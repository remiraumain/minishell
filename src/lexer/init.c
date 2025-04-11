/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 09:08:07 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/11 11:03:30 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe_error(t_token *tokens, t_global_data *data)
{
	t_token	*current;
	int		is_first;

	current = tokens;
	is_first = 1;
	while (current)
	{
		if ((is_first && current->type == TK_PIPE) || (!current->next
				&& current->type == TK_PIPE))
		{
			ft_putstr_fd("bash: syntax error near unexpected token '|'\n", 2);
			data->status = 2;
			return (0);
		}
		is_first = 0;
		current = current->next;
	}
	return (1);
}

void	process_input(char *input, t_global_data *data)
{
	t_token	*tokens;
	t_cmd	*cmds;

	if (*input)
		add_history(input);
	tokens = lexer(input, data);
	if (!tokens)
		return ;
	if (!check_pipe_error(tokens, data))
	{
		free_token_list(tokens);
		return ;
	}
	cmds = parse_line(tokens);
	free_token_list(tokens);
	if (!cmds)
		return ;
	execute_cmds(cmds, data);
	free_cmd_list(cmds);
}

t_global_data	*init_global_data(char **envp)
{
	t_global_data	*data;

	data = malloc(sizeof(t_global_data));
	if (!data)
		return (NULL);
	data->envp = init_env(envp);
	if (!data->envp)
	{
		free(data);
		return (NULL);
	}
	data->status = 0;
	data->line_count = 1;
	return (data);
}

int	clean_exit(t_global_data *data)
{
	clear_env(data->envp);
	free(data);
	rl_clear_history();
	printf("exit\n");
	return (0);
}

void	handle_signal(t_global_data *data)
{
	if (g_sig)
	{
		data->status = 130;
		g_sig = 0;
	}
}
