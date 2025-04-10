/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:40:01 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/10 16:49:30 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_sig = 0;

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

static void	process_input(char *input, t_global_data *data)
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



static t_global_data *init_global_data(char **envp)
{
    t_global_data *data = malloc(sizeof(t_global_data));
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


static int clean_exit(t_global_data *data)
{
    clear_env(data->envp);
    free(data);
    rl_clear_history();
    printf("exit\n");
    return (0);
}

static void    handle_signal(t_global_data *data)
{
    if (g_sig)
    {
        data->status = 130;
        g_sig = 0;
    }
}


int    main(int argc, char **argv, char **envp)
{
    char            *input;
    t_global_data    *data;
    (void)argc;
    (void)argv;
    
    data = init_global_data(envp);
    if (!data)
        return (0);
    while (1)
    {
        if (g_sig != -29)
            g_sig = 0;
        set_parent_signals();
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

