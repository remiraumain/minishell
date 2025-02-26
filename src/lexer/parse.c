/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:34:11 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/26 08:34:12 by nolecler         ###   ########.fr       */
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

// int	parse_quotes(t_token **head, int *index, char *input)
// {
// 	t_token	*new_token;
// 	char	*quoted_str;
// 	char	quote;

// 	quote = input[*index];
// 	quoted_str = read_quoted(input, index, quote);
// 	if (!quoted_str)
// 		return (0);
// 	new_token = create_token(TK_WORD, quoted_str);
// 	if (!new_token)
// 	{
// 		free(quoted_str);
// 		return (0);
// 	}
// 	if (quote == '\'')
// 		new_token->expand = false;
// 	else
// 		new_token->expand = true;
// 	add_token(head, new_token);
// 	return (1);
// }

int	parse_word(t_token **head, int *index, char *input, t_global_data *data)
{
	t_token	*new_token;
	char	*word;

	word = read_word_and_expand(input, index, data);
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
