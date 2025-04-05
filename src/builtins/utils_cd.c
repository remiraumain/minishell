/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:50:16 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/05 10:05:58 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_value(t_envp *envp, char *str)
{
	t_envp	*var;

	var = envp;
	while (var)
	{
		if (!ft_strcmp(var->name, str))
			return (var->value);
		var = var->next;
	}
	return (NULL);
}

void	update_old_pwd(t_envp *envp, const char *old_pwd)
{
	t_envp	*var;
	
	if (old_pwd == NULL)
		old_pwd = get_var_value(envp, "PWD");
	var = envp;
	while (var)
	{
		if (ft_strcmp(var->name, "OLDPWD") == 0)
		{
			free(var->value);
			var->value = ft_strdup(old_pwd);
			return ;
		}
		var = var->next;
	}
}

void	update_pwd(t_envp *envp, const char *new_pwd)
{
	t_envp	*var;
	
	var = envp;
	while (var)
	{
		if (ft_strcmp(var->name, "PWD") == 0)
		{
			free(var->value);
			var->value = ft_strdup(new_pwd);
			return ;
		}
		var = var->next;
	}
}

char	*get_var_home(t_envp *envp)
{
	t_envp	*var;

	var = envp;
	while (var)
	{
		if (var->name && ft_strcmp(var->name, "HOME") == 0)
			return (var->value);
		var = var->next;
	}
	ft_putstr_fd("cd: HOME not set\n", 2);
	return (NULL);
}

int	cd_slash(t_cmd *cmd, char *pwd)
{
	int	res;

	res = print_error(cmd->argv[1]);
	if (res == 1)
	{
		free(pwd);
		return (1);
	}
	return (0);
}
