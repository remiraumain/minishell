/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:22:47 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/25 12:31:28 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// good version
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

static int is_var_exist(char *argv, t_global_data *data)
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

static int is_var_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (1);
		i++;
	}
	return (0);
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

void fct(t_cmd *cmd, t_global_data *data)
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
			//return (1);// ne quitte pas, passe a l'argument suivant
			//code_status = 1;
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
			return (1);
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
		fct(cmd, data);
	return (0);
}














