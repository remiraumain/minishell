/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:46:32 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/11 11:15:49 by nolecler         ###   ########.fr       */
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

static char	*get_variable_substring(const char *input, int *index, int varlen)
{
	char	*var;

	var = ft_substr(input, *index, varlen - *index);
	if (!var)
		return (NULL);
	*index = varlen;
	return (var);
}

static char	*handle_variable_expansion(const char *input, int *index,
		int varlen, t_global_data *data)
{
	char	*var;

	var = get_variable_substring(input, index, varlen);
	if (!var)
		return (NULL);
	expand_word(&var, data);
	return (var);
}

static char	*extract_expanded_substring(const char *input, int start, int end,
		t_global_data *data)
{
	char	*substring;

	substring = ft_substr(input, start, end - start);
	if (!substring)
		return (NULL);
	expand_word(&substring, data);
	return (substring);
}

static char	*extract_and_finalize_chunk(const char *input, int len, char **word,
		t_global_data *data)
{
	char	*chunk;
	char	*substring;

	substring = extract_expanded_substring(input, 0, len, data);
	if (!substring)
	{
		free(*word);
		*word = NULL;
		return (NULL);
	}
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
			word = handle_variable_expansion(input, index, varlen, data);
			if (!word)
				return (NULL);
			return (word);
		}
		(*index)++;
	}
	chunk = extract_and_finalize_chunk(input + start, *index - start, &word,
			data);
	return (chunk);
}

// static char	*extract_and_finalize_chunk(const char *input, int start,
		//int end,
// 		char **word, t_global_data *data)
// {
// 	char	*chunk;
// 	char	*substring;

// 	substring = ft_substr(input, start, end - start);
// 	if (!substring)
// 	{
// 		free(*word);
// 		*word = NULL;
// 		return (NULL);
// 	}
// 	expand_word(&substring, data);
// 	chunk = ft_strjoin(*word, substring);
// 	free(substring);
// 	free(*word);
// 	return (chunk);
// }

// char	*add_unquoted_chunk(const char *input, int *index, t_global_data *data,
// 		char *word)
// {
// 	int		start;
// 	char	*chunk;
// 	int		varlen;

// 	start = *index;
// 	while (input[*index] && !is_stop_char(input[*index]))
// 	{
// 		if (input[*index] == '$' && input[*index + 1]
// 			&& !is_whitespace(input[*index + 1]))
// 		{
// 			varlen = *index + 1;
// 			while ((ft_isalpha(input[varlen]) || input[varlen] == '_'
// 					|| input[varlen] == '-' || input[varlen] == '?')
// 				&& !is_whitespace(input[varlen]))
// 				varlen++;
// 			word = handle_variable_expansion(input, index, varlen, data);
// 			if (!word)
// 				return (NULL);
// 			return (word);
// 		}
// 		(*index)++;
// 	}
// 	chunk = extract_and_finalize_chunk(input , start, *index, &word, data);
// 	return (chunk);
// }
