/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:57:43 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/19 18:46:00 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_argv(t_cmd *cmd, const char *word)
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

static int	check_and_add_redir(t_cmd *cmd, t_token **current)
{
	t_token_type	token_type;
	t_redir_type	redir_type;

	token_type = (*current)->type;
	*current = (*current)->next;
	if (!(*current) || (*current)->type != TK_WORD)
		return (0);
	if (token_type == TK_REDIR_IN)
		redir_type = REDIR_IN;
	else if (token_type == TK_REDIR_OUT)
		redir_type = REDIR_OUT;
	else if (token_type == TK_REDIR_APPEND)
		redir_type = REDIR_OUT_APPEND;
	else
		redir_type = REDIR_HEREDOC;
	if (!add_redir(cmd, redir_type, (*current)->value))
		return (0);
	return (1);
}

static int	apply_type(t_cmd *cmd, t_token **current)
{
	t_token_type	type;

	type = (*current)->type;
	if (type == TK_WORD)
	{
		if (!add_argv(cmd, (*current)->value))
			return (0);
	}
	else if (type == TK_REDIR_IN || type == TK_REDIR_OUT
		|| type == TK_REDIR_APPEND || type == TK_HEREDOC)
	{
		if (!check_and_add_redir(cmd, current))
			return (0);
	}
	else
		return (0);
	return (1);
}

static t_cmd	*parse_command(t_token **current)
{
	t_cmd	*cmd;

	cmd = create_cmd();
	if (!cmd)
		return (NULL);
	while (*current && (*current)->type != TK_PIPE
		&& (*current)->type != TK_EOF)
	{
		if (!apply_type(cmd, current))
		{
			free_cmd_list(cmd);
			return (NULL);
		}
		*current = (*current)->next;
	}
	return (cmd);
}

t_cmd	*parse_line(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_token	*current;
	t_cmd	*cmd;

	head = NULL;
	tail = NULL;
	current = tokens;
	while (current && current->type != TK_EOF)
	{
		cmd = parse_command(&current);
		if (!cmd)
		{
			free_cmd_list(head);
			return (NULL);
		}
		if (!head)
			head = cmd;
		else
			tail->next = cmd;
		tail = cmd;
		if (current && current->type == TK_PIPE)
			current = current->next;
	}
	return (head);
}
