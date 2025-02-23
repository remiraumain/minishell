/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:24:46 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/23 08:35:09 by rraumain         ###   ########.fr       */
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
