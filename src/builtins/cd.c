/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:05:31 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/11 09:42:42 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// test a gerer creer un dossier(ou fichier) le supprimer puis verifier pwd

static char	*get_old_pwd(char **envp)
{
	int		i;
	char	*old_pwd;
	int		len;
	
	if (!envp || !envp[0])
	{
		ft_putstr_fd("get_old_pwd failed : envp doesn't exist or is empty\n", 2);
		return (NULL);
	}
	i = 0;
	old_pwd = NULL;
	while (envp[i])
	{
		len = ft_strlen(envp[i]) - 7;
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
		{
			old_pwd = ft_substr(envp[i], 7, len); // malloc, a free ailleurs
			return (old_pwd);
		}
		i++;
	}
	return (NULL);
}

static void update_old_pwd(char **envp, const char *new_old_pwd)
{
    int i;
    
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
        {
            envp[i] = ft_strjoin("OLDPWD=", new_old_pwd); // malloc
            return;
        }
        i++;
    }
}

static void update_pwd(char **envp, const char *new_pwd)
{
    int i;

    i = 0;

    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PWD=", 4) == 0)
        {
            envp[i] = ft_strjoin("PWD=", new_pwd);
            return;
        }
        i++;
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

// cas de too many argument	A FAIRE
// verifie si c'est un dossier// 
int exec_cd(t_cmd *cmd, t_pid_data *pdata, t_global_data *sdata)
{
    char *pwd;
    char *path;
	int res;
	char *old_pwd;
	char *new_pwd;
    char *home;
	
	res = 0;
	pwd = getcwd(NULL, 0); // malloc
	old_pwd = get_old_pwd(sdata->envp);// malloc qui n est pas free encore
	path = NULL;
	new_pwd = NULL;
	home = NULL;
	if (pdata->nb_cmd == 1)
	{
		if (old_pwd) // a voir , test a faire sans et avec;
			update_old_pwd(sdata->envp, old_pwd);
		if ((!cmd->argv[1]) || (cmd->argv[1] && ft_strcmp(cmd->argv[1], "~") == 0)) // cd ou cd ~
		{
			home = getenv("HOME"); // a changer il faut faire une fonction qui chercher HOME
            if (!home || chdir(home) == -1)
            {
                ft_putstr_fd("cd: HOME not set\n", 2);
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
				free(pwd);
				return (1);
			}
			pwd = getcwd(NULL, 0);
			free(path);
		}
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


