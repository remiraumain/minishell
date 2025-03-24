/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:50:16 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/24 15:47:52 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// char	*get_old_pwd(t_envp *envp)
// {
// 	t_envp *var;
    
//     if (!envp)
//     {
//         ft_putstr_fd("get_old_pwd failed: envp is NULL or empty\n", 2);
//         return (NULL);
//     }
//     var = envp;
//     while (var)
//     {
//         if (ft_strncmp(var->name, "OLDPWD", 6) == 0)
//             return (ft_strdup(var->value));
//         var = var->next;
//     }
//     return (NULL);
// }

void update_old_pwd(t_envp *envp, const char *old_pwd)
{
    t_envp *var;
    
	var = envp;
    while (var)
    {
        if (ft_strncmp(var->name, "OLDPWD", 6) == 0)
        {
			free(var->value);
			var->value = ft_strdup(old_pwd);
            return;
        }
        var = var->next;
    }
}


void update_pwd(t_envp*envp, const char *new_pwd)
{
   t_envp *var;

   var = envp;
    while (var)
    {
        if (ft_strncmp(var->name, "PWD", 3) == 0)
        {
			free(var->value);
			var->value = ft_strdup(new_pwd);
            return;
        }
        var = var->next;
    }
}

int print_error(char *argv)
{
	if (access(argv, F_OK) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(argv , 2);
		ft_putstr_fd(": No such file or directory ", 2);
		return (1);
	}
	if (access(argv, X_OK) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(argv , 2);
		ft_putstr_fd(": permission denied ", 2);
		return (1);
	}
	if (chdir(argv) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(argv , 2);	
		ft_putstr_fd(": not a directory ", 2);
		return (1);
	}
	return (0);
}

char *get_var_home(t_envp *envp)
{
    t_envp *var;
	
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