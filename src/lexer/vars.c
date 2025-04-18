/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:34:31 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/18 12:43:05 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_varname(char *input, int *i)
{
	int		j;
	char	*name;

	if (!input)
		return (NULL);
	(*i)++;
	if (input[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	j = *i;
	while (input[j] && (ft_isalnum(input[j]) || input[j] == '_'))
		j++;
	name = ft_substr(input, *i, j - *i);
	*i = j;
	return (name);
}

char	*get_var_value(char *varname, t_global_data *data)
{
	t_envp	*env_node;
	char	*dup_val;

	if (!varname || !data)
		return (NULL);
	if (ft_strcmp(varname, "?") == 0)
		return (ft_itoa(data->status));
	env_node = search_var(data->envp, varname);
	if (!env_node || !env_node->value)
		return (ft_strdup(""));
	dup_val = ft_strdup(env_node->value);
	return (dup_val);
}
