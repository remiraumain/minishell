/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:22:47 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/19 17:21:33 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
		while(var)
		{
			printf("declare -x ");
			printf("%s=%c%s%c\n", var->name, c, var->value, c);
			var = var->next;
		}
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
	return (0);
}
