/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:38:20 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/25 15:30:05 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_word(char **word, t_global_data *data)
{
	char	*tmp;
	int		i;

	i = 0;
	while ((*word)[i])
	{
		if ((*word)[i] == '$')
		{
			tmp = expand_var(*word, &i, data);
			free(*word);
			*word = tmp;
		}
		else
			i++;
	}
}

char	*read_word_and_expand(const char *input, int *index, t_global_data *data)
{
	char	*word;
	char	*substring;
	char	*tmp;
	int		start;
	char	quote;

	word = ft_strdup("");
	if (!word)
		return (NULL);
	while (input[*index] != '\0' && !is_whitespace(input[*index])
		&& input[*index] != '|' && input[*index] != '<' && input[*index] != '>')
	{
		if (input[*index] == '\'' || input[*index] == '"')
		{
			quote = input[*index];
			substring = read_quoted(input, index, quote);
			if (!substring)
			{
				free(word);
				return (NULL);
			}
			if (quote == '"')
				expand_word(&substring, data);
			tmp = ft_strjoin(word, substring);
		}
		else
		{
			start = *index;
			while (input[*index] &&  !is_whitespace(input[*index])
				&& input[*index] != '\''&& input[*index] != '"'
				&& input[*index] != '|' && input[*index] != '<'
				&& input[*index] != '>')
				*index = *index + 1;
			substring = ft_substr(input, start, *index - start);
			expand_word(&substring, data);
			tmp = ft_strjoin(word, substring);
		}
		free(substring);
		free(word);
		if (!tmp)
			return (NULL);
		word = tmp;
	}
	return (word);
}

char	*read_quoted(const char *input, int *index, char quote)
{
	int		start;
	int		i;
	char	*word;

	i = *index + 1;
	start = i;
	while (input[i] && input[i] != quote)
		i++;
	if (!input[i])
		return (NULL);
	word = ft_substr(input, start, i - start);
	if (!word)
		return (NULL);
	*index = i + 1;
	return (word);
}

t_token_type	check_redir(const char *input, int *index)
{
	if (input[*index] == '<')
	{
		if (input[*index + 1] == '<')
		{
			*index = *index + 2;
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
