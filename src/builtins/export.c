/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:45:55 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/15 11:26:27 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_value(t_global_data *data, char *argv)
{
	t_envp	*var;
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
		if (ft_strncmp(argv, var->name, len) == 0
			&& len == ft_strlen(var->name))
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

static void	update_value_with_join(t_global_data *data, char *argv)
{
	t_envp	*var;
	size_t	len;
	char	*val;
	char	*new_value;

	val = ft_strnstr(argv, "+=", ft_strlen(argv));
	if (!val)
		return ;
	len = ft_strlen(argv) - ft_strlen(val);
	var = data->envp;
	while (var)
	{
		if (ft_strncmp(argv, var->name, len) == 0
			&& len == ft_strlen(var->name))
		{
			new_value = ft_strjoin(var->value, val + 2);
			free(var->value);
			var->value = new_value;
			break ;
		}
		var = var->next;
	}
}

static int	export_with_args(t_cmd *cmd, t_global_data *data)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		if (is_var_valid(cmd->argv[i]) == 1)
		{
			print_message(cmd, ": not a valid identifier\n");
			data->status = 1;
		}
		else
		{
			if (ft_strnstr(cmd->argv[i], "+=", ft_strlen(cmd->argv[i])))
				update_value_with_join(data, cmd->argv[i]);
			else if (is_var_exist(cmd->argv[i], data) == 1)
				add_var_in_env(cmd->argv[i], data->envp);
			else if (ft_strchr(cmd->argv[i], '='))
				update_value(data, cmd->argv[i]);
		}
		i++;
	}
	return (data->status);
}

static void	print_sorted_env(t_envp *var)
{
	ft_sort_params(var);
	while (var)
	{
		if (ft_strcmp(var->name, "_") != 0)
		{
			printf("declare -x %s", var->name);
			if (var->value)
				printf("=\"%s\"", var->value);
			printf("\n");
		}
		var = var->next;
	}
}

int	exec_export(t_cmd *cmd, t_global_data *data)
{
	t_envp	*var;
	char	**temp;

	if (!cmd->argv[1])
	{
		temp = convert_env(data->envp);
		if (!temp)
			return (1);
		var = init_env(temp);
		if (!var)
			return (1);
		clear_env_array(temp);
		if (!data->envp)
		{
			ft_putstr_fd("Error: envp is empty or NULL\n", 2);
			data->status = 1;
			return (data->status);
		}
		print_sorted_env(var);
		clear_env(var);
	}
	else
		data->status = export_with_args(cmd, data);
	return (data->status);
}
