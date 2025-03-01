/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:05:31 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/01 13:01:22 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// char * getcwd( char *buffer, size_t size ); renvoie le pwd actuel
// char * getenv( const char * varName ); ex: char *oldpwd = getenv("OLDPWD")
// verif sur cd tout court
// int chdir( const char * path );
// cas de cd fichier.txt -> cd: not a directory: test.c return (1)



// A FAIRE 
// Fonction pour mettre à jour OLD_PWD dans l'environnement
// void update_old_pwd(char **envp, const char *new_old_pwd)

// Fonction pour mettre à jour PWD dans l'environnement
// void update_pwd(char **envp, const char *new_pwd)
	
static char	*get_old_pwd(char **envp)
{
	int		i;
	int		j;
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
		j = ft_strlen(envp[i]);
		len = j - 7;
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
		{
			old_pwd = ft_substr(envp[i], 7, len); // malloc, a free ailleurs
			return (old_pwd);
		}
		i++;
	}
	return (NULL);
}

static int print_error(char *argv)
{
	if (access(argv, F_OK) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(argv, 2);
		return (1);
	}
	if (access(argv, X_OK) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd("permission denied: ", 2);
		ft_putstr_fd(argv, 2);
		return (1);
	}
	if (chdir(argv) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd("not a directory: ", 2);
		ft_putstr_fd(argv, 2);	
		return (1);
	}
	return (0);
}


// verifie si c'est un dossier// int stat(const char *pathname, struct stat *buf); A FAIRE PLUS TARD
int exec_cd(t_cmd *cmd, t_pid_data *pdata, t_global_data *sdata)
{
    char *pwd;
    char *path;
	int res;
	char *old_pwd;
	
	res = 0;
	pwd = getcwd(NULL, 0); // allocation
	old_pwd = get_old_pwd(sdata->envp);// malloc qui n est pas free encore
	path = NULL;
	if (pdata->nb_cmd == 1) //if (argc == 3)
	{
		if (ft_strcmp(cmd->argv[0], "cd") == 0 && cmd->argv[1] && cmd->argv[1][0] == '/') // verif a renforcer
		{
			res = print_error(cmd->argv[1]);
			if (res == 1)
			{
				free(old_pwd);
				return (1);
			}
			free(pwd);
			pwd = getcwd(NULL, 0); // allocation
		}
		else if (ft_strcmp(cmd->argv[0],"cd") == 0 && cmd->argv[1])
		{
			if (ft_strcmp(cmd->argv[1], "~") != 0 && ft_strcmp(cmd->argv[1], "..") != 0)
			{
				path = ft_strjoin(pwd, cmd->argv[1]); // malloc Ã free
				res = print_error(cmd->argv[1]);
				if (res == 1)
				{
					free (old_pwd);
					free(path);
					return (1);
				}
				free (pwd);
				pwd = getcwd(NULL, 0);
				free(path);
			}
		}
		// else if(a gerer plus tard cd ~ , cd .. et cd tout court)
		else if (ft_strcmp(cmd->argv[0], "cd") == 0 && cmd->argv[1] && ft_strcmp(cmd->argv[1], "..") == 0)
		{
			if (chdir("..") == -1)
			{
				ft_putstr_fd("cd: ", 2);
				ft_putstr_fd("not a directory: ", 2);
				ft_putstr_fd(cmd->argv[1], 2);	
				free (old_pwd);
				return (1);
			}	
		}
	}
	free (pwd);
	free (old_pwd);
	return (0);
}


