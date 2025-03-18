/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:24:39 by rraumain          #+#    #+#             */
/*   Updated: 2025/03/18 18:42:40 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_and_wait(t_pid_data *pdata)
{
	int	i;
	int	status;

	i = 0;
	while (i < pdata->nb_cmd - 1)
	{
		close(pdata->pipefd[i][0]);
		close(pdata->pipefd[i][1]);
		i++;
	}
	i = 0;
	while (i < pdata->nb_cmd && !g_sig)
	{
		waitpid(pdata->pids[i], &status, 0);
		i++;
	}
}

static void	execute_child(t_cmd *cmd, int index, t_pid_data *pdata)
{
	int		i;
	char	*path;
	char 	**env;

	dup_fd(pdata, index);
	i = 0;
	while (i < pdata->nb_cmd - 1)
	{
		close(pdata->pipefd[i][0]);
		close(pdata->pipefd[i][1]);
		i++;
	}
	if (!apply_redirections(cmd, index))
		exit(EXIT_FAILURE);
	if (is_builtin_child(cmd) == 1)
	{
		exec_builtin_child(cmd, pdata, pdata->gdata);
		exit(pdata->gdata->status);
	}
	env = convert_env(pdata->gdata->envp);
	path = get_command_path(cmd->argv[0], pdata->gdata->envp);
	if (!path)
	{
		perror(cmd->argv[0]);
		exit(127);
	}
	execve(path, cmd->argv, env);
	free(path);
	perror(cmd->argv[0]);
	exit(EXIT_FAILURE);
}

static int	fork_and_exec_child(t_cmd *cmd, int i, t_pid_data *pdata)
{
	pid_t	pid;

	if (cmd->redir && (cmd->redir->type == REDIR_HEREDOC
			|| cmd->redir->type == REDIR_HEREDOC_Q)
		&& !set_heredoc(cmd->redir, pdata->gdata) && !g_sig)
	{
		perror("heredoc");
		return (0);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (0);
	}
	set_child_signals();
	if (pid == 0)
		execute_child(cmd, i, pdata);
	pdata->pids[i] = pid;
	return (1);
}

static void	process_cmds(t_cmd *cmd, t_pid_data *pdata, t_global_data *data)
{
	t_cmd	*head;
	int		i;

	head = cmd;
	pdata->pids = malloc(sizeof(pid_t) * pdata->nb_cmd);
	if (!pdata->pids)
		return ;
	ft_bzero(pdata->pids, sizeof(pid_t) * pdata->nb_cmd);
	i = 0;
	while (cmd && !g_sig)
	{
		if (is_builtin_parent(cmd) == 1)
			exec_builtin_parent(cmd, pdata, data);
		else if (!fork_and_exec_child(cmd, i, pdata))
			break ;
		i++;
		cmd = cmd->next;
	}
	close_and_wait(pdata);
	clean_heredocs(head, i);
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
