/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 23:40:41 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/12 12:02:16 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_redirect(t_token **head, int *index, char *input)
{
	t_token			*new_token;
	t_token_type	type;

	type = check_redir(input, index);
	new_token = create_token(type, NULL);
	if (!new_token)
		return (0);
	add_token(head, new_token);
	return (1);
}

int	parse_word(t_token **head, int *index, char *input)
{
	t_token	*new_token;
	char	*word;

	word = read_word(input, index);
	if (!word)
		return (0);
	new_token = create_token(TK_WORD, word);
	if (!new_token)
	{
		free(word);
		return (0);
	}
	add_token(head, new_token);
	return (1);
}
