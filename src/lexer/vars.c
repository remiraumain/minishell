/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:44:06 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/25 14:55:48 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *varname, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(varname);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], varname, len) == 0
			&& envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*replace_var(char *token, int start, int varname_len, char *value)
{
	char	*expanded;
	int		value_len;
	int		after;

	if (!token)
		return (NULL);
	after = ft_strlen(&token[start + varname_len]);
	value_len = ft_strlen(value);
	expanded = malloc(start + value_len + after + 1);
	if (!expanded)
		return (NULL);
	ft_memcpy(expanded, token, start);
	ft_memcpy(&expanded[start], value, value_len);
	ft_memcpy(&expanded[start + value_len],
		&token[start + varname_len], after);
	expanded[start + value_len + after] = '\0';
	return (expanded);
}
