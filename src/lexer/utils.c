/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:38:20 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/23 20:41:39 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_word(const char *input, int *index)
{
	int		start;
	char	*word;
	int		i;

	i = 0;
	start = *index;
	while (input[start + i] != '\0' && !is_whitespace(input[start + i]))
	{
		if (input[*index] == '|'
			|| input[*index] == '<'
			|| input[*index] == '>')
			break ;
		i++;
	}
	*index += i;
	word = ft_substr(input, start, i);
	return (word);
}

char	*read_quoted(const char *input, int *index)
{
	char	*word;
	char	quote;
	int		start;
	int		i;

	if (!input || !index)
		return (NULL);
	quote = input[*index];
	*index = *index + 1;
	start = *index;
	while (input[*index] && input[*index] != quote)
		*index = *index + 1;
	if (!input[*index])
		return (NULL);
	i = *index;
	if (input[*index])
		*index = *index + 1;
	word = ft_substr(input, start, i);
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
