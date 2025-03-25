/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:05:31 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/25 12:30:55 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int cd_home(t_global_data *sdata, char *pwd)
{
	char *home;
	
	home = get_var_home(sdata->envp);
	if (!home || chdir(home) == -1)
	{
		free(pwd);
		return (1);
	}
	update_old_pwd(sdata->envp, pwd);
    update_pwd(sdata->envp, getcwd(NULL, 0));
    free(pwd);
    return (0);
}

static int cd_dot(t_cmd *cmd, t_global_data *sdata, char *pwd)
{
    t_envp  *old;
    char    *dest;
    
    old = search_var(sdata->envp, "OLDPWD");
    if (ft_strcmp(old->value, pwd) == 0)
        dest = "..";
    else
        dest = old->value;
    if (chdir(dest) == -1)
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(cmd->argv[1], 2);	
        ft_putstr_fd(": not a directory ", 2);
        free(pwd);
        return (1);
    }
    if (!pwd)
        pwd = ft_strdup(dest);
    update_old_pwd(sdata->envp, pwd);
    update_pwd(sdata->envp, getcwd(NULL, 0));
    free(pwd);
    return (0);
}

static int process_cd(char *path, char *pwd, t_cmd *cmd, t_global_data *sdata)
{
    int res;
    
    res = print_error(cmd->argv[1]);
    if (res == 1)
    {
        free(path);
        free(pwd);
        return (1);
    }
    if (chdir(path) == -1)
    {
        free(path);
        free(pwd);
        return (1);
    }
    update_old_pwd(sdata->envp, pwd);
    update_pwd(sdata->envp, getcwd(NULL, 0));
    free(path);
    free(pwd);
    return (0);
}


static int cd_relative(t_cmd *cmd, t_global_data *sdata, char *pwd)
{
    char *path;
    int result;

    pwd = ft_strjoin(pwd, "/");
    if (!pwd)
        return (1);
    path = ft_strjoin(pwd, cmd->argv[1]);
    if (!path)
    {
        free(pwd);
        return (1);
    }
    result = process_cd(path, pwd, cmd, sdata);
    return (result);
}


int exec_cd(t_cmd *cmd, t_pid_data *pdata, t_global_data *sdata)
{
    char *pwd;
	
    pwd = getcwd(NULL, 0);
    if (pdata->nb_cmd == 1)
    {
        if (!cmd->argv[1] || ft_strcmp(cmd->argv[1], "~") == 0)
            return (cd_home(sdata, pwd));
        if (ft_strcmp(cmd->argv[1], "..") == 0 || ft_strcmp(cmd->argv[1], "-") == 0)
            return (cd_dot(cmd, sdata, pwd));
        if (cmd->argv[1][0] == '/')
            return (cd_slash(cmd, pwd));
        return (cd_relative(cmd, sdata, pwd));
    }
    free(pwd);
    return (0);
}

