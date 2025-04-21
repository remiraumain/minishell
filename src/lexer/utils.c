/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:38:20 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/21 14:00:56 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_word(const char *input, int *index)
{
	char	*str;
	char	*tmp;
	char	*old_str;

	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (input[*index] && !is_whitespace(input[*index])
		&& !is_inset(input[*index], "|<>"))
	{
		if (input[*index] == '\'' || input[*index] == '\"')
			tmp = process_quoted_word(input, index);
		else
			tmp = process_unquoted_text(input, index);
		if (!tmp)
		{
			free(str);
			return (NULL);
		}
		old_str = str;
		str = ft_strjoin(str, tmp);
		free(old_str);
		free(tmp);
	}
	return (str);
}

static t_token_type	parse_heredoc(const char *input, int *index)
{
	int	tmp;
	int	start;

	*index += 2;
	tmp = *index;
	while (is_whitespace(input[tmp]))
		tmp++;
	start = tmp;
	if (input[tmp] == '"' || input[tmp] == '\'')
	{
		*index = start;
		return (TK_HEREDOC_QUOTES);
	}
	while (input[tmp] && !is_whitespace(input[tmp])
		&& input[tmp] != '"' && input[tmp] != '\'')
		tmp++;
	if (input[tmp] == '"' || input[tmp] == '\'')
	{
		*index = start;
		return (TK_HEREDOC_QUOTES);
	}
	*index = start;
	return (TK_HEREDOC);
}

t_token_type	check_redir(const char *input, int *index)
{
	if (input[*index] == '<' && input[*index + 1] == '<')
		return (parse_heredoc(input, index));
	if (input[*index] == '<')
	{
		(*index)++;
		return (TK_REDIR_IN);
	}
	if (input[*index] == '>' && input[*index + 1] == '>')
	{
		*index += 2;
		return (TK_REDIR_APPEND);
	}
	if (input[*index] == '>')
	{
		(*index)++;
		return (TK_REDIR_OUT);
	}
	return (TK_EOF);
}
