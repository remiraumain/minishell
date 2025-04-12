/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:38:20 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/12 14:16:26 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:38:20 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/12 12:58:52 by rraumain         ###   ########.fr       */
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
			if (input[*index + 1] == '\"' || input[*index + 1] == '\'')
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
