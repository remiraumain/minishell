/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:58:02 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/15 16:10:56 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	new_token(t_token **head, int *index)
{
	t_token	*new_token;

	new_token = create_token(TK_PIPE, NULL);
	if (!new_token)
		return (0);
	add_token(head, new_token);
	*index = *index + 1;
	return (1);
}

static int	parse(t_token **head, char *input, int *index, t_global_data *data)
{
	char	*word;
	char	*expanded;
	t_token	*new_tkn;

	if (input[*index] == '|')
		return (new_token(head, index));
	else if (input[*index] == '<' || input[*index] == '>')
		return (parse_redirect(head, index, input));
	else
	{
		word = read_word(input, index);
		if (!word)
			return (0);
		if (tokenlast(*head) && (tokenlast(*head)->type == TK_HEREDOC
			|| tokenlast(*head)->type == TK_HEREDOC_QUOTES))
			new_tkn = create_token(TK_WORD, word);
		else
		{
			expanded = expand_line(word, data);
			new_tkn = create_token(TK_WORD, expanded);
			free(word);
		}
		if (!new_tkn)
		{
			if (expanded)
				free(expanded);
			return (0);
		}
		add_token(head, new_tkn);
		return (1);
	}
}

t_token	*lexer(char *input, t_global_data *data)
{
	t_token	*head;
	int		index;

	head = NULL;
	index = 0;
	while (input[index])
	{
		while (input[index] && is_whitespace(input[index]))
			index++;
		if (!input[index])
			return (head);
		if (!parse(&head, input, &index, data))
		{
			free_token_list(head);
			return (NULL);
		}
	}
	return (head);
}
