/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:40:01 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/19 18:53:35 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Temporary function to print command details
static void	print_redirections(t_redir *redir)
{
	while (redir)
	{
		printf("\n    type: ");
		if (redir->type == REDIR_IN)
			printf("<");
		else if (redir->type == REDIR_OUT)
			printf(">");
		else if (redir->type == REDIR_OUT_APPEND)
			printf(">>");
		else if (redir->type == REDIR_HEREDOC)
			printf("<<");
		printf(" file: [%s]", redir->filename);
		redir = redir->next;
	}
}

static void	print_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		printf("[%s] ", argv[i]);
		i++;
	}
}

static void	print_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		printf("Command:\n");
		printf("  argv: ");
		if (cmd->argv)
			print_argv(cmd->argv);
		else
			printf("(empty)");
		printf("\n");
		printf("  redirections: ");
		if (cmd->redir)
			print_redirections(cmd->redir);
		else
			printf("(none)");
		printf("\n");
		cmd = cmd->next;
		if (cmd)
			printf("  pipe to next command\n");
	}
}

static void	process_input(char *input, t_data *data)
{
	t_token	*tokens;
	t_cmd	*cmds;

	(void)data;
	if (*input)
		add_history(input);
	tokens = lexer(input);
	if (!tokens)
		return ;
	cmds = parse_line(tokens);
	if (!cmds)
		printf("erreur de parsing... a gerer plus tard (voir bash)\n");
	else
	{
		print_cmd(cmds);
		free_cmd_list(cmds);
	}
	free_token_list(tokens);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	data;

	(void)argc;
	(void)argv;
	data.env = env;
	(void)data;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			return (0);
		process_input(input, &data);
		free(input);
	}
	rl_clear_history();
	return (0);
}
