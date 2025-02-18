/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:58:02 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/17 00:00:48 by rraumain         ###   ########.fr       */
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

static int	parse(t_token **head, char *input, int *index)
{
	int	status;

	if (input[*index] == '|')
		status = new_token(head, index);
	else if (input[*index] == '<' || input[*index] == '>')
		status = parse_redirect(head, index, input);
	else if (input[*index] == '"' || input[*index] == '\'')
		status = parse_quotes(head, index, input);
	else
		status = parse_word(head, index, input);
	return (status);
}

t_token	*lexer(char *input)
{
	t_token	*head;
	int		index;

	head = NULL;
	index = 0;
	while (input[index] != '\0')
	{
		while (input[index] != '\0' && is_whitespace(input[index]))
			index = index + 1;
		if (input[index] == '\0')
			return (head);
		if (parse(&head, input, &index) == 0)
		{
			free_token_list(head);
			return (NULL);
		}
	}
	return (head);
}
