/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:38:20 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/03 17:13:33 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_quoted(const char *input, int *index, char quote)
{
	int		start;
	int		i;
	char	*word;

	i = *index + 1;
	start = i;
	while (input[i] && input[i] != quote)
		i++;
	if (!input[i])
	{
		perror("Bad input");
		return (NULL);
	}
	word = ft_substr(input, start, i - start);
	if (!word)
		return (NULL);
	*index = i + 1;
	return (word);
}

static char	*add_quoted_chunk(const char *input, int *index,
		t_global_data *data, char *word)
{
	char	quote;
	char	*substring;
	char	*chunk;

	quote = input[*index];
	substring = read_quoted(input, index, quote);
	if (!substring)
	{
		free(word);
		return (NULL);
	}
	if (quote == '"')
		expand_word(&substring, data);
	chunk = ft_strjoin(word, substring);
	free(substring);
	free(word);
	return (chunk);
}

static char	*add_unquoted_chunk(const char *input, int *index,
		t_global_data *data, char *word)
{
	int		start;
	char	*substring;
	char	*chunk;
	int		varlen;
	char	*var;

	start = *index;
	while (input[*index] && !is_whitespace(input[*index])
		&& input[*index] != '\'' && input[*index] != '"' && input[*index] != '|'
		&& input[*index] != '<' && input[*index] != '>')
	{
		if (input[*index] == '$' && input[*index + 1]
			&& !is_whitespace(input[*index + 1]))
		{
			varlen = *index;
			varlen++;
			while ((ft_isalpha(input[varlen]) || input[varlen] == '_'
					|| input[varlen] == '-' || input[varlen] == '?')
				&& !is_whitespace(input[varlen]))
				varlen++;
			var = ft_substr(input, start, varlen - start);
			if (var)
			{
				expand_word(&var, data);
				free(word);
				word = var;
				*index = varlen;
				return (word);
			}
		}
		*index = *index + 1;
	}
	substring = ft_substr(input, start, *index - start);
	if (!substring)
	{
		free(word);
		return (NULL);
	}
	expand_word(&substring, data);
	chunk = ft_strjoin(word, substring);
	free(substring);
	free(word);
	return (chunk);
}

char	*read_word_and_expand(const char *input, int *index,
		t_global_data *data)
{
	char	*word;
	char	*tmp;

	word = ft_strdup("");
	if (!word)
		return (NULL);
	while (input[*index] != '\0' && !is_whitespace(input[*index])
		&& input[*index] != '|' && input[*index] != '<' && input[*index] != '>')
	{
		if (input[*index] == '\'' || input[*index] == '"')
			tmp = add_quoted_chunk(input, index, data, word);
		else
			tmp = add_unquoted_chunk(input, index, data, word);
		if (!tmp)
			return (NULL);
		word = tmp;
	}
	return (word);
}

t_token_type	check_redir(const char *input, int *index)
{
	if (input[*index] == '<')
	{
		if (input[*index + 1] == '<')
		{
			*index = *index + 2;
			if (input[*index + 1] == '"' || input[*index + 1] == '\'')
				return (TK_HEREDOC_QUOTES);
			return (TK_HEREDOC);
		}
		*index = *index + 1;
		return (TK_REDIR_IN);
	}
	else if (input[*index] == '>')
	{
		if (input[*index + 1] == '>')
		{
			*index = *index + 2;
			return (TK_REDIR_APPEND);
		}
		*index = *index + 1;
		return (TK_REDIR_OUT);
	}
	return (TK_EOF);
}
