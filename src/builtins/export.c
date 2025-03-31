/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:22:47 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/31 17:35:37 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	add_var_in_env(char *str, t_envp *envp)
{
	t_envp	*last;
	t_envp	*new;
	int		i;

	i = ft_envlen(envp);
	new = init_var(str, i);
	if (!new)
	{
		clear_env(envp);
		return ;
	}
	if (!envp)
		envp = new;
	else
	{
		last = ft_lastenv(envp);
		last->next = new;
	}
	i++;
}


static void	update_value(t_global_data *data, char *argv)
{
	t_envp *var;
	size_t	len;
	char	*val;

	val = ft_strchr(argv, '=');
	if (val)
		len = ft_strlen(argv) - ft_strlen(val);
	else
		len = ft_strlen(argv);
	var = data->envp;
	while (var)
	{
		if (ft_strncmp(argv, var->name, len) == 0)
		{
			free(var->value);
			if (val)
				var->value = ft_strdup(val + 1);
			else
				var->value = NULL;
		}
		var = var->next;
	}
}

static int export_with_args(t_cmd *cmd, t_global_data *data)
{
	int i;
	
	i = 1;
	while (cmd->argv[i])
	{
		if (is_var_valid(cmd->argv[i]) == 1)
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(cmd->argv[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			data->status = 1;
		}
		else 
		{
			if (is_var_exist(cmd->argv[i], data) == 1)
				add_var_in_env(cmd->argv[i], data->envp);
			else
				update_value(data, cmd->argv[i]);
		}
		i++;
	}
	return (data->status);
}


int exec_export(t_cmd *cmd, t_global_data *data)
{
	t_envp *var;
	
	var = data->envp;
	if (!cmd || !cmd->argv || !cmd->argv[1])
	{
		if (!data->envp)
		{
			printf("Error: envp is empty or NULL\n");
			data->status = 1;
			return (data->status);
		}
		ft_sort_params(data->envp);
		while(var)
		{
			printf("declare -x %s", var->name);
			if (var->value)
				printf("=\"%s\"",var->value);
			printf("\n");
			var = var->next;
		}
	}
	else
		data->status = export_with_args(cmd, data);
	return (data->status);
}
