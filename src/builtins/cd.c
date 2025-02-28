/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:05:31 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/28 14:52:03 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// char * getcwd( char *buffer, size_t size ); renvoie le pwd actuel
// char * getenv( const char * varName ); ex: char *oldpwd = getenv("OLDPWD")
// verif sur cd tout court
// int chdir( const char * path );
// cas de cd fichier.txt -> cd: not a directory: test.c return (1)

int exec_cd(t_cmd *cmd, t_pid_data *pdata)
{
    char *pwd;
    char *path;
	pwd = getcwd(NULL, 0); // allocation
	path = NULL;
	if (pdata->nb_cmd == 1) //if (argc == 3)
	{
		if (ft_strcmp(cmd->argv[0], "cd") == 0 && cmd->argv[1] && cmd->argv[1][0] == '/') // verif a renforcer
		{
			if (access(cmd->argv[1], F_OK) == -1)
			{
				ft_putstr_fd("cd: ", 2);
				ft_putstr_fd("no such file or directory: ", 2);
				ft_putstr_fd(cmd->argv[1], 2);
				return (1);
			}
			if (access(cmd->argv[1], X_OK) == -1)
			{
				ft_putstr_fd("cd: ", 2);
				ft_putstr_fd("permission denied: ", 2);
				ft_putstr_fd(cmd->argv[1], 2);
				return (1);
			}
			// verifie si c'est un dossier// int stat(const char *pathname, struct stat *buf); A FAIRE PLUS TARD
			if (chdir(cmd->argv[1]) == -1)
			{
				ft_putstr_fd("cd: ", 2);
				ft_putstr_fd("not a directory: ", 2);
				ft_putstr_fd(cmd->argv[1], 2);
				
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
				if (access(path, F_OK) == -1)
				{
					ft_putstr_fd("cd: ", 2);
					ft_putstr_fd("no such file or directory: ", 2);
					ft_putstr_fd(cmd->argv[1], 2);
					free (path);
					return (1);
				}
				if (access(path, X_OK) == -1)
				{
					ft_putstr_fd("cd: ", 2);
					ft_putstr_fd("permission denied: ", 2);
					ft_putstr_fd(cmd->argv[1], 2);
					free (path);
					return (1);
				}
				if (chdir(path) == -1)
				{
					ft_putstr_fd("cd: ", 2);
					ft_putstr_fd("not a directory: ", 2);
					ft_putstr_fd(cmd->argv[1], 2);
					free (path);
					return (1);
				}
				free (pwd);
				pwd = getcwd(NULL, 0);
				free(path);
			}
		}
		
		// else if(a gerer plus tard cd ~ , cd .. et cd tout court)
	}
	free (pwd);
	return (0);
}
