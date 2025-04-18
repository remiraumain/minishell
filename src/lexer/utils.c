/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:38:20 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/18 17:43:15 by nolecler         ###   ########.fr       */
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

t_token_type	check_redir(const char *input, int *index)
{
	if (input[*index] == '<')
	{
		if (input[*index + 1] == '<')
		{
			*index += 2;
			while (is_whitespace(input[*index]))
				*index += 1;
			// check if quotes at the end
			// if quote at beginning then do not check whitespace
			if (input[*index] == '\"' || input[*index] == '\'')
				return (TK_HEREDOC_QUOTES);
			return (TK_HEREDOC);
		}
		*index += 1;
		return (TK_REDIR_IN);
	}
	if (input[*index] == '>')
	{
		if (input[*index + 1] == '>')
		{
			*index += 2;
			return (TK_REDIR_APPEND);
		}
		*index += 1;
		return (TK_REDIR_OUT);
	}
	return (TK_EOF);
}
