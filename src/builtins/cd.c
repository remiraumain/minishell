/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:05:31 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/24 15:49:43 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// test a gerer creer un dossier(ou fichier) le supprimer puis verifier pwd
// cas de too many arguments a verifier


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
	if (chdir(cmd->argv[1]) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);	
		ft_putstr_fd(": not a directory ", 2);
		free(pwd);
		return (1);
	}
	update_old_pwd(sdata->envp, pwd);
    update_pwd(sdata->envp, getcwd(NULL, 0));
    free(pwd);
    return (0);
}


static int cd_slash(t_cmd *cmd, char *pwd)
{
	int res;
	
    res = print_error(cmd->argv[1]);
    if (res == 1)
    {
        free(pwd);
        return (1);
    }
    return (0);
}

static int cd_relative(t_cmd *cmd, t_global_data *sdata, char *pwd)
{
	char *path;
	int res;
	
    path = ft_strjoin(pwd, cmd->argv[1]);
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


int exec_cd(t_cmd *cmd, t_pid_data *pdata, t_global_data *sdata)
{
    int res;
    char *pwd;
	
	res = 0;
    pwd = getcwd(NULL, 0);
    if (pdata->nb_cmd == 1)
    {
        if (!cmd->argv[1] || ft_strcmp(cmd->argv[1], "~") == 0)
            return (cd_home(sdata, pwd));
        if (ft_strcmp(cmd->argv[1], "..") == 0 || ft_strcmp(cmd->argv[1], "-") == 0)// cd - a tester
            return (cd_dot(cmd, sdata, pwd));
        if (cmd->argv[1][0] == '/')
            return (cd_slash(cmd, pwd));
        return (cd_relative(cmd, sdata, pwd));
    }
    free(pwd);
    return (0);
}

