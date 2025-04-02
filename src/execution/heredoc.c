/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:49:26 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/02 17:33:30 by nolecler         ###   ########.fr       */
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

	set_heredoc_signals();
	while (1)
	{
		input = readline("> ");
		if (!input)
			break;
		if (ft_strncmp(input, redir->delimeter, INT_MAX) == 0 || g_sig)
		{
			free(input);
			break ;
		}
		if (redir->type == REDIR_HEREDOC)
			expand_word(&input, data);
		// add_history(input); // History deactivated because it was annoying
		ft_putendl_fd(input, fd);
		free(input);
	}
	set_parent_signals();
}

int	set_heredoc(t_redir	*redir, t_global_data *data)
{
	int		fd;

	while (redir && !g_sig)
	{
		if (redir->type == REDIR_HEREDOC || redir->type == REDIR_HEREDOC_Q)
		{
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return (0);
			readline_loop(redir, fd, data);
			close(fd);
		}
		redir = redir->next;
	}
	return (1);
}

void	clean_heredocs(t_cmd *cmd)
{
	int		i;
	t_redir	*redir;

	i = 0;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC || redir->type == REDIR_HEREDOC_Q)
				unlink(redir->filename);
			redir = redir->next;
		}
		i++;
		cmd = cmd->next;
	}
}
