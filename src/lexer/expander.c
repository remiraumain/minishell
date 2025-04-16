/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:43:49 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/16 12:12:22 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_var(char **buf, char *input, int *i, t_global_data *data)
{
	char	*name;
	char	*value;
	char	*tmp;

	name = get_varname(input, i);
	if (!name)
		return ;
	value = get_var_value(name, data);
	if (!value)
		value = ft_strdup("");
	tmp = ft_strjoin(*buf, value);
	free(*buf);
	*buf = tmp;
	free(value);
	free(name);
}

static int	process_single_quote_block(const char *line, int i, char **expanded)
{
	i++;
	while (line[i] && line[i] != '\2')
	{
		copy_char(expanded, line[i]);
		i++;
	}
	if (line[i] == '\2')
		i++;
	return (i);
}

static int	process_double_quote_block(const char *line, int i, char **expanded,
	t_global_data *data)
{
	i++;
	while (line[i] && line[i] != '\4')
	{
		if (line[i] == '$' && (ft_isalpha(line[i + 1]) || line[i + 1] == '_'
				|| line[i + 1] == '?'))
			handle_var(expanded, (char *)line, &i, data);
		else
		{
			copy_char(expanded, line[i]);
			i++;
		}
	}
	if (line[i] == '\4')
		i++;
	return (i);
}

static int	process_unquoted_block(const char *line, int i, char **expanded,
	t_global_data *data)
{
	char	*res;

	res = NULL;
	if (line[i] == '$' && (ft_isalpha(line[i + 1]) || line[i + 1] == '_'
			|| line[i + 1] == '?'))
	{
		handle_var(expanded, (char *)line, &i, data);
		res = trim_whitespace(*expanded);
		free(*expanded);
		*expanded = res;
	}
	else
	{
		copy_char(expanded, line[i]);
		i++;
	}
	return (i);
}

char	*expand_line(char *line, t_global_data *data)
{
	int		i;
	char	*expanded;

	i = 0;
	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	while (line && line[i])
	{
		if (line[i] == '\1')
			i = process_single_quote_block(line, i, &expanded);
		else if (line[i] == '\3')
			i = process_double_quote_block(line, i, &expanded, data);
		else
			i = process_unquoted_block(line, i, &expanded, data);
	}
	return (expanded);
}
