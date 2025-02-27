/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:49:26 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/27 21:47:18 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_heredoc_filename_part2(char *cmd_id, char *redir_id)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*filename;

	tmp1 = ft_strdup(".heredoc_temp_");
	if (!tmp1)
		return (NULL);
	tmp2 = ft_strjoin(tmp1, cmd_id);
	free(tmp1);
	free(cmd_id);
	if (!tmp2)
		return (NULL);
	tmp3 = ft_strjoin(tmp2, "_");
	free(tmp2);
	if (!tmp3)
		return (NULL);
	filename = ft_strjoin(tmp3, redir_id);
	free(tmp3);
	free(redir_id);
	return (filename);
}

char	*create_heredoc_filename(int cmd_i, int redir_i)
{
	char	*filename;
	char	*cmd_id;
	char	*redir_id;

	cmd_id = ft_itoa(cmd_i);
	if (!cmd_id)
		return (NULL);
	redir_id = ft_itoa(redir_i);
	if (!redir_id)
	{
		free(cmd_id);
		return (NULL);
	}
	filename = create_heredoc_filename_part2(cmd_id, redir_id);
	if (!filename)
		perror("malloc tempfile heredoc fail");
	return (filename);
}

static void	readline_loop(t_redir *redir, int fd, t_global_data *data)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input)
			break ;
		if (ft_strncmp(input, redir->filename, ft_strlen(redir->filename)) == 0
			&& ft_strlen(input) == ft_strlen(redir->filename))
		{
			free(input);
			break ;
		}
		expand_word(&input, data);
		// add_history(input); History deactivated because it was annoying
		ft_putendl_fd(input, fd);
		free(input);
	}
}

int	set_heredoc(t_cmd *cmd, int cmd_i, t_global_data *data)
{
	int		fd;
	char	*filename;
	int		redir_i;
	t_redir	*redir;

	redir_i = 0;
	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			filename = create_heredoc_filename(cmd_i, redir_i);
			if (!filename)
				return (0);
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			free(filename);
			if (fd < 0)
				return (0);
			readline_loop(redir, fd, data);
			close(fd);
			redir_i++;
		}
		redir = redir->next;
	}
	return (1);
}

void	clean_heredocs(t_cmd *cmd, int len)
{
	char	*filename;
	int		redir_i;
	int		cmd_i;
	t_redir	*redir;

	cmd_i = -1;
	while (cmd && cmd_i++ < len)
	{
		redir_i = 0;
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				filename = create_heredoc_filename(cmd_i, redir_i++);
				if (filename)
				{
					unlink(filename);
					free(filename);
				}
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
