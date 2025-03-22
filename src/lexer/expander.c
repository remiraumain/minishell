/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:43:49 by rraumain          #+#    #+#             */
/*   Updated: 2025/03/22 11:17:50 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_varname(char *token, int start, int *len)
{
	int		i;
	char	*varname;

	*len = 1;
	if (token[start + 1] == '?')
	{
		varname = ft_strdup("?");
		if (!varname)
			return (NULL);
		*len = 2;
		return (varname);
	}
	i = start + 1;
	while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
		i++;
	*len = (i - start);
	varname = ft_substr(token, start + 1, *len - 1);
	return (varname);
}

static char	*get_var_value(char *varname, t_global_data *data)
{
	t_envp	*envp;//modif
	char	*value;

	if (!varname || !data->envp)
	//if (!varname || !data->lst_envp)
		return (NULL);
	if (varname[0] == '?' && varname[1] == '\0')
	{
		value = ft_itoa(data->status);
		return (value);
	}
	//value = get_env_value(varname, data->envp);
	envp = NULL;
	//value = get_env_value(varname, data->lst_envp);
	envp = search_var(data->envp, varname);//modif
	//if (!value)
	if (!envp)//modif
		return ("");
	//return (value);
	return (envp->name);
}

static char	*expand_var(char *token, int *index, t_global_data *data)
{
	char	*varname;
	char	*value;
	char	*expanded;
	int		len;

	len = 0;
	varname = get_varname(token, *index, &len);
	if (!varname)
		return (token);
	value = get_var_value(varname, data);
	expanded = replace_var(token, *index, len, value);
	if (varname[0] == '?' && value)
		free(value);
	free(varname);
	if (!expanded)
		return (token);
	*index += ft_strlen(value);
	return (expanded);
}

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
