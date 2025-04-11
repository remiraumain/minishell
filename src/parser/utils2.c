/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:25:41 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/11 11:31:39 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	*init_redir(int index, t_redir_type type)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->index = index;
	new_redir->type = type;
	new_redir->delimeter = NULL;
	new_redir->filename = NULL;
	new_redir->next = NULL;
	return (new_redir);
}

static int	initialize_heredoc_redir(t_redir *redir, t_cmd *cmd, char *filename,
		int index)
{
	redir->delimeter = ft_strdup(filename);
	if (!redir->delimeter)
		return (0);
	redir->filename = create_heredoc_filename(cmd->index, index);
	if (!redir->filename)
	{
		free(redir->delimeter);
		return (0);
	}
	return (1);
}

static void	add_current_redir(t_cmd *cmd, t_redir *new_redir)
{
	t_redir	*tail;

	tail = cmd->redir;
	if (!tail)
		cmd->redir = new_redir;
	else
	{
		while (tail->next)
			tail = tail->next;
		tail->next = new_redir;
	}
}

int	add_redir(t_cmd *cmd, t_redir_type type, char *filename, int index)
{
	t_redir	*new_redir;

	new_redir = init_redir(index, type);
	if (!new_redir)
		return (0);
	if (type == REDIR_HEREDOC || type == REDIR_HEREDOC_Q)
	{
		if (!initialize_heredoc_redir(new_redir, cmd, filename, index))
		{
			free(new_redir);
			return (0);
		}
	}
	else
	{
		new_redir->filename = ft_strdup(filename);
		if (!new_redir->filename)
		{
			free(new_redir);
			return (0);
		}
	}
	add_current_redir(cmd, new_redir);
	return (1);
}

int	add_argv(t_cmd *cmd, const char *word)
{
	int		count;
	char	**new_argv;
	int		i;

	count = 0;
	if (cmd->argv)
	{
		while (cmd->argv[count])
			count++;
	}
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return (0);
	i = 0;
	while (i < count)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	if (!add_current_argv(new_argv, i, word))
		return (0);
	free(cmd->argv);
	cmd->argv = new_argv;
	return (1);
}
