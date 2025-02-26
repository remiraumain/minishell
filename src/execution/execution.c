/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:33:15 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/26 14:13:50 by nolecler         ###   ########.fr       */
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

static void	dup_fd(t_pid_data *pdata, int index)
{
	if (index > 0)
	{
		if (dup2(pdata->pipefd[index - 1][0], STDIN_FILENO) < 0)
		{
			perror("dup2 in");
			exit(1);
		}
	}
	if (index < pdata->nb_cmd - 1)
	{
		if (dup2(pdata->pipefd[index][1], STDOUT_FILENO) < 0)
		{
			perror("dup2 out");
			exit(1);
		}
	}
}

static void	execute_child(t_cmd *cmd, int index, t_pid_data *pdata, t_global_data *data)
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
	if (!apply_redirections(cmd))
		exit(EXIT_FAILURE);
	if (is_builtin(cmd) == 1)
	{
		exec_builtin(cmd, data);
		return ;
	}
	path = get_command_path(cmd->argv[0], data->envp);
	if (!path)
	{
		perror(cmd->argv[0]);
		exit(127);
	}
	execve(path, cmd->argv, data->envp);
	free(path);
	perror(cmd->argv[0]);
	exit(EXIT_FAILURE);
}

static void	process_cmds(t_cmd *cmd, t_pid_data *pdata, t_global_data *data)
{
	int		i;
	pid_t	pid;

	pdata->pids = malloc(sizeof(pid_t) * pdata->nb_cmd);
	if (!pdata->pids)
		return ;
	i = 0;
	while (cmd)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			free(pdata->pids);
			free(pdata);
			return ;
		}
		if (pid == 0)
			execute_child(cmd, i, pdata, data);
		pdata->pids[i] = pid;
		i++;
		cmd = cmd->next;
	}
	close_and_wait(pdata);
	free(pdata->pids);
}

void	execute_cmds(t_cmd *cmd, t_global_data *data)
//void	execute_cmds(t_cmd *cmd, char **envp)
{
	t_pid_data	*pdata;

	pdata = malloc(sizeof(t_pid_data));
	if (!pdata)
		return ;
	//pdata->envp = envp;
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
	process_cmds(cmd, pdata, data);
	cleanup_pipes(pdata->pipefd, pdata->nb_cmd - 1);
	free(pdata);
}
