/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:24:46 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/22 14:09:21 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	cleanup_pipes(int **pipefd, int count)
{
	while (count > 0)
	{
		count--;
		close(pipefd[count][0]);
		close(pipefd[count][1]);
		free(pipefd[count]);
	}
	free(pipefd);
}

static void	init_pipes(int **pipefd, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pipe(pipefd[i]) < 0)
		{
			cleanup_pipes(pipefd, count);
			perror("pipe");
			return ;
		}
		i++;
	}
}

int	**create_pipes(int count)
{
	int	**pipefd;
	int	i;

	if (count == 0)
		return (NULL);
	pipefd = malloc(sizeof(int *) * count);
	if (!pipefd)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		pipefd[i] = malloc(sizeof(int) * 2);
		if (!pipefd[i])
		{
			cleanup_pipes(pipefd, i);
			perror("malloc");
			return (NULL);
		}
		i++;
	}
	init_pipes(pipefd, count);
	return (pipefd);
}

void	dup_fd(t_pid_data *pdata, int index, t_cmd *cmd)
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
		if (!is_builtin_parent(cmd->next)
			&& dup2(pdata->pipefd[index][1], STDOUT_FILENO) < 0)
		{
			perror("dup2 out");
			exit(1);
		}
	}
}
