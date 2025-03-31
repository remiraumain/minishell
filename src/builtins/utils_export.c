/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:33:00 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/31 17:35:27 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_sort_params(t_envp *env)
{
    t_envp *i;
    t_envp *j;                
    char *tmp_name;          
    char *tmp_value;         

    if (env == NULL || env->next == NULL)
        return;
    i = env;
    while (i != NULL)
    {
        j = i->next;
        while (j != NULL)
        {
            if (ft_strcmp(i->name, j->name) > 0)
            {
                tmp_name = i->name;
                i->name = j->name;
                j->name = tmp_name;
                tmp_value = i->value;
                i->value = j->value;
                j->value = tmp_value;
            }
            j = j->next;
        }
        i = i->next;
    }
}

int is_var_valid(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=' || (str[i] >= '0' &&  str[i] <= '9'))
		return (1);
	else
	{
		while (str[i] && str[i] != '=')
		{
			if (!(ft_isalnum(str[i]) || str[i] == '_'))
				return (1);
			i++;
		}
	}
	return (0);
}

int is_var_exist(char *argv, t_global_data *data)
{
	t_envp	*tmp;
	size_t	len;
	char	*val;

	if (!data->envp)
		return (1);
	tmp = data->envp;
	val = ft_strchr(argv, '=');
	if (val)
		len = ft_strlen(argv) - ft_strlen(val);
	else
		len = ft_strlen(argv);
	while (tmp)
	{
		if (ft_strncmp(argv, tmp->name, len) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}