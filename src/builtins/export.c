/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:22:47 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/20 12:46:30 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void ft_sort_params(t_envp *env)
{
    t_envp *i;                // Pointeur pour parcourir la liste
    t_envp *j;                // Pointeur pour comparer les éléments
    char *tmp_name;          // Variable temporaire pour échanger les noms
    char *tmp_value;         // Variable temporaire pour échanger les valeurs

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

int exec_export(t_cmd *cmd, t_global_data *data)
{
	t_envp *var;
	char c;

	var = data->envp;
	c = '"';
	if (!cmd || !cmd->argv || !cmd->argv[1]) // export sans argument
	{
		if (!data->envp)
		{
			printf("Error: envp is empty or NULL\n");
			return (1);
		}
		ft_sort_params(data->envp);
		while(var)
		{
			printf("declare -x %s=%c%s%c\n", var->name, c, var->value, c);
			var = var->next;
		}
	}
	return (0);
}




	/*
	char **env;
	int i;
	
	(void)cmd;
	env = convert_env(data->envp);
	i = 0;
	while (env[i])
	{
		printf("declare -x ");
		printf("%s\n", env[i]);
		i++;
	}
	clear_env_array(env);*/


