/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:46:32 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/10 15:11:46 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_stop_char(char c)
{
	if (is_whitespace(c) || c == '\'' || c == '"' || c == '|' || c == '<'
		|| c == '>')
		return (true);
	return (false);
}

static char	*handle_variable_expansion(const char *input, int *index,
		int varlen, t_global_data *data, char *word)
{
	char	*var;
	char	*result;

	var = ft_substr(input, *index, varlen - *index);
	if (!var)
		return (NULL);
	expand_word(&var, data);
	result = var;
	free(word);
	*index = varlen;
	return (result);
}

static char	*extract_and_finalize_chunk(const char *input, int start, int end,
		char **word, t_global_data *data)
{
	char	*chunk;
	char	*substring;

	substring = ft_substr(input, start, end - start);
	if (!substring)
	{
		free(*word);
		*word = NULL;
		return (NULL);
	}
	expand_word(&substring, data);
	chunk = ft_strjoin(*word, substring);
	free(substring);
	free(*word);
	return (chunk);
}

char	*add_unquoted_chunk(const char *input, int *index, t_global_data *data,
		char *word)
{
	int		start;
	char	*chunk;
	int		varlen;

	start = *index;
	while (input[*index] && !is_stop_char(input[*index]))
	{
		if (input[*index] == '$' && input[*index + 1]
			&& !is_whitespace(input[*index + 1]))
		{
			varlen = *index + 1;
			while ((ft_isalpha(input[varlen]) || input[varlen] == '_'
					|| input[varlen] == '-' || input[varlen] == '?')
				&& !is_whitespace(input[varlen]))
				varlen++;
			word = handle_variable_expansion(input, index, varlen, data, word);
			if (!word)
				return (NULL);
			return (word);
		}
		(*index)++;
	}
	chunk = extract_and_finalize_chunk(input, start, *index, &word, data);
	return (chunk);
}

/*
static char	*add_unquoted_chunk(const char *input, int *index,
	t_global_data *data, char *word)
{
int			start;
char		*substring;
char		*chunk;
int			varlen;
char		*var;

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
}*/