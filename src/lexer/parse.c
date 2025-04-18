/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 23:40:41 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/18 12:43:37 by nolecler         ###   ########.fr       */
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

static int	is_quotes_space(char c)
{
	if (c == '\01'
		|| c == '\02'
		|| c == '\03'
		|| c == '\04'
		|| is_whitespace(c))
		return (1);
	return (0);
}

static void	clean_quotes_space(char **word)
{
	size_t	i;
	char	*res;

	res = NULL;
	i = 0;
	while ((*word)[i])
	{
		if (!is_quotes_space((*word)[i]))
			copy_char(&res, (*word)[i]);
		i++;
	}
	free(*word);
	*word = res;
}

static t_token	*create_token_heredoc(char *word)
{
	int		i;
	char	*varname;
	t_token	*token;

	i = 0;
	if (!word)
		return (NULL);
	while (word[i] && is_quotes_space(word[i]))
		i++;
	if (word[i] == '$')
	{
		varname = get_varname(word, &i);
		free(word);
		if (!varname)
			return (NULL);
		token = create_token(TK_WORD, ft_strjoin("$", varname));
		free(varname);
		return (token);
	}
	clean_quotes_space(&word);
	token = create_token(TK_WORD, word);
	return (token);
}

int	parse_word(t_token **head, char *input, int *index, t_global_data *data)
{
	char	*word;
	char	*expanded;
	t_token	*new_tkn;

	word = read_word(input, index);
	if (!word)
		return (0);
	if (tokenlast(*head) && (tokenlast(*head)->type == TK_HEREDOC
			|| tokenlast(*head)->type == TK_HEREDOC_QUOTES))
		new_tkn = create_token_heredoc(word);
	else
	{
		expanded = expand_line(word, data);
		free(word);
		new_tkn = create_token(TK_WORD, expanded);
	}
	if (!new_tkn)
	{
		if (expanded)
			free(expanded);
		return (0);
	}
	add_token(head, new_tkn);
	return (1);
}
