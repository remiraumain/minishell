/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:05:31 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/24 12:37:07 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

// test a gerer creer un dossier(ou fichier) le supprimer puis verifier pwd


static char	*get_old_pwd(t_envp *envp)
{
	t_envp *var;
    
    if (!envp)
    {
        ft_putstr_fd("get_old_pwd failed: envp is NULL or empty\n", 2);
        return (NULL);
    }
    var = envp;
    while (var)
    {
        if (ft_strncmp(var->name, "OLDPWD", 6) == 0)
            return (ft_strdup(var->value));
        var = var->next;
    }
    return (NULL);
}

static void update_old_pwd(t_envp *envp, const char *new_old_pwd)
{
    t_envp *var;
    
	var = envp;
    while (var)
    {
        if (ft_strncmp(var->name, "OLDPWD", 6) == 0)
        {
			free(var->value);
			var->value = ft_strdup(new_old_pwd);
            return;
        }
        var = var->next;
    }
}


static void update_pwd(t_envp*envp, const char *new_pwd)
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

static int print_error(char *argv)
{
	if (access(argv, F_OK) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(argv , 2);
		ft_putstr_fd(": no such file or directory ", 2);
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

static char *get_var_home(t_envp *envp)
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


// cas de too many argument	A FAIRE

int exec_cd(t_cmd *cmd, t_pid_data *pdata, t_global_data *sdata)
{
    char *pwd;
    char *path;
	int res;
	char *old_pwd;
	char *new_pwd;
    char *home;
	
	res = 0;
	path = NULL;
	new_pwd = NULL;
	home = NULL;
	pwd = getcwd(NULL, 0);// malloc
	old_pwd = get_old_pwd(sdata->envp);// malloc qui n est pas free encore
	if (pdata->nb_cmd == 1)
	{
		if ((!cmd->argv[1]) || (cmd->argv[1] && ft_strcmp(cmd->argv[1], "~") == 0)) // cd ou cd ~
		{
			home = get_var_home(sdata->envp);
            if (!home || chdir(home) == -1)
            {
                free(old_pwd);
                free(pwd);
                return (1);
			}
		}
		else if (cmd->argv[1] && (ft_strcmp(cmd->argv[1], "..") == 0 || ft_strcmp(cmd->argv[1], "-") == 0)) // a revoir cd - 2fois
		{
			if (chdir("..") == -1)
			{
				ft_putstr_fd("cd: ", 2);
				ft_putstr_fd(cmd->argv[1], 2);	
				ft_putstr_fd(": not a directory ", 2);
				free (old_pwd);
				free(pwd);
				return (1);
			}
		}
		else if (cmd->argv[1] && cmd->argv[1][0] == '/') // cd /argv[1];
		{
			res = print_error(cmd->argv[1]);
			if (res == 1)
			{
				free(old_pwd);
				free(pwd);
				return (1);
			}
		}
		else if (cmd->argv[1])
		{
			path = ft_strjoin(pwd, cmd->argv[1]); // malloc Ã free
			free(pwd);//
			res = print_error(cmd->argv[1]);
			if (res == 1)
			{
				free (old_pwd);
				free(path);
				free(pwd);//
				return (1);
			}
			pwd = getcwd(NULL, 0);
			free(path);
		}
		update_old_pwd(sdata->envp, pwd);
		new_pwd = getcwd(NULL, 0);
        if (new_pwd)
        {
			update_pwd(sdata->envp, new_pwd);
            free(new_pwd);
        }
	}
	free (pwd);
	free (old_pwd);
	return (0);
}