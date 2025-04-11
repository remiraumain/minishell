/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:54:39 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/11 12:34:40 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_and_wait(t_pid_data *pdata)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < pdata->nb_cmd - 1)
	{
		close(pdata->pipefd[i][0]);
		close(pdata->pipefd[i][1]);
		i++;
	}
	i = 0;
	while (i < pdata->nb_cmd)
	{
		if (pdata->pids[i] > 0)
			waitpid(pdata->pids[i], &status, 0);
		if (WIFEXITED(status))
			pdata->gdata->status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			pdata->gdata->status = 128 + WTERMSIG(status);
		i++;
	}
	if (pdata->gdata->status == 131)
		ft_putstr_fd("Quit\n" ,1);
}

int	is_directory(const char *path)
{
	struct stat	sb;

	return (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode));
}

void	exit_clean_child(t_pid_data *pdata, t_cmd *head, int status)
{
	if (pdata)
	{
		free(pdata->pids);
		cleanup_pipes(pdata->pipefd, pdata->nb_cmd - 1);
		clear_env(pdata->gdata->envp);
		free(pdata->gdata);
		free(pdata);
	}
	free_cmd_list(head);
	exit(status);
}

void	dup_and_close(t_pid_data *pdata, int index, t_cmd *cmd)
{
	int	i;

	i = 0;
	dup_fd(pdata, index, cmd);
	while (i < pdata->nb_cmd - 1)
	{
		close(pdata->pipefd[i][0]);
		close(pdata->pipefd[i][1]);
		i++;
	}
}

void	exec_builtin_child_and_free(t_cmd *cmd, t_pid_data *pdata, t_cmd *head)
{
	exec_builtin_child(cmd, pdata, pdata->gdata);
	free(pdata->pids);
	cleanup_pipes(pdata->pipefd, pdata->nb_cmd - 1);
	clear_env(pdata->gdata->envp);
	free(pdata->gdata);
	free(pdata);
	free_cmd_list(head);
}
