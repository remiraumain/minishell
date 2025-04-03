/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:46:09 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/03 17:14:55 by nolecler         ###   ########.fr       */
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

static int	check_and_add_redir(t_cmd *cmd, t_token **current, int *index)
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
	{
		*index = *index + 1;
		if (token_type == TK_HEREDOC)
			redir_type = REDIR_HEREDOC;
		else
			redir_type = REDIR_HEREDOC_Q;
	}
	if (!add_redir(cmd, redir_type, (*current)->value, *index))
		return (0);
	return (1);
}

static int	apply_type(t_cmd *cmd, t_token **current, int *index)
{
	t_token_type	type;

	type = (*current)->type;
	if (type == TK_WORD)
	{
		if ((*current)->value[0] == '\0')
			return (1);
		if (!add_argv(cmd, (*current)->value))
			return (0);
	}
	else if (type == TK_REDIR_IN || type == TK_REDIR_OUT
		|| type == TK_REDIR_APPEND || type == TK_HEREDOC
		|| type == TK_HEREDOC_QUOTES)
	{
		if (!check_and_add_redir(cmd, current, index))
			return (0);
	}
	else
		return (0);
	return (1);
}

static t_cmd	*parse_command(t_token **current, int index)
{
	t_cmd	*cmd;
	int		i;

	cmd = create_cmd(index);
	if (!cmd)
		return (NULL);
	i = -1;
	while (*current && (*current)->type != TK_PIPE
		&& (*current)->type != TK_EOF)
	{
		if (!apply_type(cmd, current, &i))
		{
			free_cmd_list(cmd);
			return (NULL);
		}
		*current = (*current)->next;
	}
	return (cmd);
}

static int	handle_command_node(t_token **current, t_cmd **head, t_cmd **tail,
		int *i)
{
	t_cmd	*cmd;

	cmd = parse_command(current, *i);
	if (!cmd)
	{
		free_cmd_list(*head);
		return (0);
	}
	if (!*head)
		*head = cmd;
	else
		(*tail)->next = cmd;
	*tail = cmd;
	if (*current && (*current)->type == TK_PIPE)
	{
		*current = (*current)->next;
		(*i)++;
	}
	return (1);
}

t_cmd	*parse_line(t_token *tokens)
{
	int		i;
	t_cmd	*head;
	t_cmd	*tail;
	t_token	*current;

	head = NULL;
	tail = NULL;
	current = tokens;
	i = 0;
	while (current && current->type != TK_EOF)
	{
		if (!handle_command_node(&current, &head, &tail, &i))
			return (NULL);
	}
	return (head);
}
