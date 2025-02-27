/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:24:39 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/27 21:05:20 by rraumain         ###   ########.fr       */
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
	while (i < pdata->nb_cmd)
	{
		waitpid(pdata->pids[i], &status, 0);
		i++;
	}
}

static void	execute_child(t_cmd *cmd, int index, t_pid_data *pdata)
{
	int		i;
	char	*path;

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
	path = get_command_path(cmd->argv[0], pdata->envp);
	if (!path)
	{
		perror(cmd->argv[0]);
		exit(127);
	}
	execve(path, cmd->argv, pdata->envp);
	free(path);
	perror(cmd->argv[0]);
	exit(EXIT_FAILURE);
}

static int	fork_and_exec_child(t_cmd *cmd, int i, t_pid_data *pdata,
	t_cmd *head)
{
	pid_t	pid;

	if (cmd->redir && cmd->redir->type == REDIR_HEREDOC
		&& !set_heredoc(cmd, i))
	{
		free(pdata->pids);
		free(pdata);
		clean_heredocs(head, i);
		return (0);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(pdata->pids);
		free(pdata);
		return (0);
	}
	if (pid == 0)
		execute_child(cmd, i, pdata);
	pdata->pids[i] = pid;
	return (1);
}

static void	process_cmds(t_cmd *cmd, t_pid_data *pdata)
{
	t_cmd	*head;
	int		i;

	head = cmd;
	pdata->pids = malloc(sizeof(pid_t) * pdata->nb_cmd);
	if (!pdata->pids)
		return ;
	i = 0;
	while (cmd)
	{
		if (!fork_and_exec_child(cmd, i, pdata, head))
			break ;
		i++;
		cmd = cmd->next;
	}
	close_and_wait(pdata);
	clean_heredocs(head, i);
	free(pdata->pids);
}

void	execute_cmds(t_cmd *cmd, char **envp)
{
	t_pid_data	*pdata;

	pdata = malloc(sizeof(t_pid_data));
	if (!pdata)
		return ;
	pdata->envp = envp;
	pdata->nb_cmd = count_cmds(cmd);
	if (pdata->nb_cmd == 0)
	{
		free(pdata);
		return ;
	}
	pdata->pipefd = create_pipes(pdata->nb_cmd);
	if (!pdata->pipefd)
	{
		free(pdata);
		return ;
	}
	process_cmds(cmd, pdata);
	cleanup_pipes(pdata->pipefd, pdata->nb_cmd - 1);
	free(pdata);
}
