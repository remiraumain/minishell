/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:35:03 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/11 10:12:19 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

// Temporary function to print command details
// static void	print_redirections(t_redir *redir)
// {
// 	while (redir)
// 	{
// 		printf("\n    type: ");
// 		if (redir->type == REDIR_IN)
// 			printf("<");
// 		else if (redir->type == REDIR_OUT)
// 			printf(">");
// 		else if (redir->type == REDIR_OUT_APPEND)
// 			printf(">>");
// 		else if (redir->type == REDIR_HEREDOC)
// 			printf("<<");
// 		printf(" file: [%s]", redir->filename);
// 		redir = redir->next;
// 	}
// }

// static void	print_argv(char **argv)
// {
// 	int	i;

// 	i = 0;
// 	while (argv[i])
// 	{
// 		printf("[%s] ", argv[i]);
// 		i++;
// 	}
// }

// static void	print_cmd(t_cmd *cmd)
// {
// 	while (cmd)
// 	{
// 		printf("Command:\n");
// 		printf("  argv: ");
// 		if (cmd->argv)
// 			print_argv(cmd->argv);
// 		else
// 			printf("(empty)");
// 		printf("\n");
// 		printf("  redirections: ");
// 		if (cmd->redir)
// 			print_redirections(cmd->redir);
// 		else
// 			printf("(none)");
// 		printf("\n");
// 		cmd = cmd->next;
// 		if (cmd)
// 			printf("  pipe to next command\n");
// 	}
// }

static void	process_input(char *input, t_global_data *data)
{
	t_token	*tokens;
	t_cmd	*cmds;

	if (*input)
		add_history(input);
	tokens = lexer(input, data);
	if (!tokens)
		return ;
	// expand_tokens(tokens, envp, status);
	cmds = parse_line(tokens);
	free_token_list(tokens);
	if (!cmds)
	{
		rl_clear_history();
		exit(EXIT_FAILURE);
	}
	else
	{
		// print_cmd(cmds);
		execute_cmds(cmds, data);
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
	// data->envp = NULL;
	data->envp = malloc(sizeof(char **));
	if (!data->envp)
	{
		free(data);
		return (1);
	}
	ft_memcpy(data->envp, envp, sizeof(char **));
	data->status = 0;
	// var_copy(envp, &(data->envp)); // modif
	while (1)
	{
		//data->envp = envp;
		input = readline("minishell> ");
		if (!input)
		{
			// free_env_copy(data->envp); //ajout
			free(data);
			rl_clear_history();
			return (0);
		}
		process_input(input, data);
		free(input);
	}
	// free_env_copy(data->envp); //ajout
	rl_clear_history();
	return (0);
}
