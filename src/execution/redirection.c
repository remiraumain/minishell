/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:50:19 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/27 22:45:52 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
	{
		perror(redir->filename);
		return (0);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static int	redir_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(redir->filename);
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static int	redir_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(redir->filename);
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static int	redir_heredoc(int cmd_i, int redir_i)
{
	int		fd;
	char	*filename;

	filename = create_heredoc_filename(cmd_i, redir_i);
	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd < 0)
		return (0);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	apply_redirections(t_cmd *cmd, int cmd_i)
{
	int		redir_i;
	t_redir	*redir;

	redir_i = 0;
	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == REDIR_IN && !redir_in(redir))
			return (0);
		else if (redir->type == REDIR_OUT && !redir_out(redir))
			return (0);
		else if (redir->type == REDIR_OUT_APPEND && !redir_append(redir))
			return (0);
		else if ((redir->type == REDIR_HEREDOC
				|| redir->type == REDIR_HEREDOC_E)
			&& !redir_heredoc(cmd_i, redir_i))
			return (0);
		redir_i++;
		redir = redir->next;
	}
	return (1);
}
