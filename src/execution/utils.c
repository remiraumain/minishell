/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:24:46 by rraumain          #+#    #+#             */
/*   Updated: 2025/03/03 23:23:33 by rraumain         ###   ########.fr       */
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
		free(pipefd[count]);
	}
	free(pipefd);
}

static int	init_pipes(int **pipefd, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		if (pipe(pipefd[i]) < 0)
		{
			cleanup_pipes(pipefd, cmd_count - 1);
			perror("pipe");
			return (0);
		}
		i++;
	}
	return (1);
}

int	**create_pipes(int cmd_count)
{
	int	**pipefd;
	int	i;

	pipefd = malloc(sizeof(int *) * (cmd_count - 1));
	if (!pipefd)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	while (i < cmd_count - 1)
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
	if (init_pipes(pipefd, cmd_count) == 0)
		return (NULL);
	return (pipefd);
}

void	dup_fd(t_pid_data *pdata, int index)
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
