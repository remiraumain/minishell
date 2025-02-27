/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:52:41 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/27 20:42:58 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	free_redir_list(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->filename);
		free(redir);
		redir = tmp;
	}
}

void	free_cmd_list(t_cmd *head)
{
	t_cmd	*tmp;
	int		i;

	while (head)
	{
		tmp = head->next;
		if (head->argv)
		{
			i = 0;
			while (head->argv[i])
			{
				free(head->argv[i]);
				i++;
			}
			free(head->argv);
		}
		free_redir_list(head->redir);
		free(head);
		head = tmp;
	}
}

int	add_redir(t_cmd *cmd, t_redir_type type, const char *filename)
{
	t_redir	*new_redir;
	t_redir	*tail;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (0);
	new_redir->type = type;
	new_redir->filename = ft_strdup(filename);
	if (!new_redir->filename)
	{
		free(new_redir);
		return (0);
	}
	new_redir->next = NULL;
	if (!cmd->redir)
		cmd->redir = new_redir;
	else
	{
		tail = cmd->redir;
		while (tail->next)
			tail = tail->next;
		tail->next = new_redir;
	}
	return (1);
}

int	add_current_argv(char **new_argv, int index, const char *word)
{
	new_argv[index] = ft_strdup(word);
	if (!new_argv[index])
	{
		while (index > 0)
		{
			index = index - 1;
			free(new_argv[index]);
		}
		free(new_argv);
		return (0);
	}
	new_argv[index + 1] = NULL;
	return (1);
}
