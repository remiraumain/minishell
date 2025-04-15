/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:24:39 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/15 15:27:27 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child(t_cmd *cmd, int index, t_pid_data *pdata, t_cmd *head)
{
	char	**env;
	char	*path;

	prepare_execution(cmd, index, pdata, head);
	env = convert_env(pdata->gdata->envp);
	path = get_command_path(cmd->argv[0], pdata->gdata->envp);
	if (!path)
		path_error(cmd, head, pdata, env);
	if (is_directory(path))
	{
		print_message(cmd, ": Is a directory\n");
		free(path);
		exit_and_clean(head, pdata, env, 126);
	}
	if (access(path, X_OK) != 0)
	{
		print_message(cmd, ": Permission denied\n");
		free(path);
		exit_and_clean(head, pdata, env, 126);
	}
	execve(path, cmd->argv, env);
	clear_env_array(env);
	free(path);
	ft_putstr_fd(cmd->argv[0], 2);
	exit(EXIT_FAILURE);
}

static int	fork_and_exec_child(t_cmd *cmd, int i, t_pid_data *pdata,
		t_cmd *head)
{
	pid_t	pid;

	if (cmd->redir && (cmd->redir->type == REDIR_HEREDOC
			|| cmd->redir->type == REDIR_HEREDOC_Q) && !set_heredoc(cmd->redir,
			pdata->gdata))
	{
		perror("heredoc");
		return (0);
	}
	if (g_sig && cmd->argv && ft_strncmp(cmd->argv[0], "echo", 5) != 0)
		return (0);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (0);
	}
	if (pid == 0)
	{
		set_child_signals();
		execute_child(cmd, i, pdata, head);
	}
	signal(SIGINT, handle_sigint_no_redisplay);
	pdata->pids[i] = pid;
	return (1);
}

static int	execution_loop(t_cmd *cmd, t_pid_data *pdata, t_global_data *data,
		t_cmd *head)
{
	int	i;

	i = 0;
	while (cmd)
	{
		if (is_builtin_parent(cmd) == 1)
		{
			if (!has_child_process(head))
			{
				exec_builtin_parent(cmd, pdata, data, head);
				clean_heredocs(head);
				free(pdata->pids);
				return (0);
			}
		}
		else if (!fork_and_exec_child(cmd, i, pdata, head))
			break ;
		i++;
		cmd = cmd->next;
	}
	return (1);
}

static void	process_cmds(t_cmd *cmd, t_pid_data *pdata, t_global_data *data)
{
	t_cmd	*head;

	head = cmd;
	pdata->pids = malloc(sizeof(pid_t) * pdata->nb_cmd);
	if (!pdata->pids)
		return ;
	ft_bzero(pdata->pids, sizeof(pid_t) * pdata->nb_cmd);
	if (execution_loop(cmd, pdata, data, head) == 0)
		return ;
	close_and_wait(pdata);
	clean_heredocs(head);
	free(pdata->pids);
}

void	execute_cmds(t_cmd *cmd, t_global_data *data)
{
	t_pid_data	*pdata;

	pdata = malloc(sizeof(t_pid_data));
	if (!pdata)
		return ;
	pdata->gdata = data;
	pdata->nb_cmd = count_cmds(cmd);
	if (pdata->nb_cmd == 0)
	{
		free(pdata);
		return ;
	}
	pdata->pipefd = create_pipes(pdata->nb_cmd - 1);
	if (!pdata->pipefd && pdata->nb_cmd - 1 > 0)
	{
		free(pdata);
		return ;
	}
	process_cmds(cmd, pdata, data);
	cleanup_pipes(pdata->pipefd, pdata->nb_cmd - 1);
	free(pdata);
}
