/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:45:50 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/15 11:45:31 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_quoted(const char *input, int *index, char quote)
{
	int		start;
	char	*word;

	start = *index;
	while (input[*index] && input[*index] != quote)
		(*index)++;
	if (!input[*index])
	{
		perror("Bad input");
		return (NULL);
	}
	word = ft_substr(input, start, *index - start);
	(*index)++;
	return (word);
}

static char	*process_single_quote(char *word)
{
	char	*wrapped;
	char	*wrapped2;

	wrapped = ft_strjoin("\1", word);
	wrapped2 = ft_strjoin(wrapped, "\2");
	free(wrapped);
	return (wrapped2);
}

static char	*process_double_quote(char *word)
{
	char	*wrapped;
	char	*wrapped2;

	wrapped = ft_strjoin("\3", word);
	wrapped2 = ft_strjoin(wrapped, "\4");
	free(wrapped);
	return (wrapped2);
}

char	*process_quoted_word(const char *input, int *index)
{
	char	quote;
	char	*tmp;
	char	*result;

	result = NULL;
	quote = input[*index];
	(*index)++;
	tmp = read_quoted(input, index, quote);
	if (!tmp)
		return (NULL);
	if (quote == '\'')
		result = process_single_quote(tmp);
	else if (quote == '"')
		result = process_double_quote(tmp);
	free(tmp);
	return (result);
}

char	*process_unquoted_text(const char *input, int *index)
{
	int		start;
	char	*result;

	start = *index;
	while (input[*index] && !is_whitespace(input[*index])
		&& !is_stop_char(input[*index]))
		(*index)++;
	result = ft_substr(input, start, *index - start);
	return (result);
}
