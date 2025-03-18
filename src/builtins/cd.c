/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:05:31 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/17 12:22:35 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// test a gerer creer un dossier(ou fichier) le supprimer puis verifier pwd

// static char	*get_old_pwd(char **envp)
// {
// 	int		i;
// 	char	*old_pwd;
// 	int		len;
	
// 	if (!envp || !envp[0])
// 	{
// 		ft_putstr_fd("get_old_pwd failed : envp doesn't exist or is empty\n", 2);
// 		return (NULL);
// 	}
// 	i = 0;
// 	old_pwd = NULL;
// 	while (envp[i])
// 	{
// 		len = ft_strlen(envp[i]) - 7;
// 		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
// 		{
// 			old_pwd = ft_substr(envp[i], 7, len); // malloc, a free ailleurs
// 			return (old_pwd);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

static void update_envp(t_envp *envp, char *name, char *new_value)
{
	while (envp)
	{
		if (ft_strcmp(envp->name, name) == 0)
		{
			free(envp->value);
			envp->value = ft_strdup(new_value);
			return;
		}
		envp = envp->next;
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
	int res;
	char *old_pwd;
	char *home;
	
	res = 0;
	pwd = getcwd(NULL, 0);
	old_pwd = pwd;
	home = NULL;

	if (pdata->nb_cmd == 1)
	{
		if (old_pwd)
			update_envp(sdata->envp, "OLDPWD", old_pwd);

		if ((!cmd->argv[1]) || (cmd->argv[1] && ft_strcmp(cmd->argv[1], "~") == 0))
		{
			home = getenv("HOME");
			if (!home || chdir(home) == -1)
			{
				ft_putstr_fd("cd: HOME not set\n", 2);
				free(pwd);
				return (1);
			}
		}
		else if (cmd->argv[1] && (ft_strcmp(cmd->argv[1], "..") == 0))
		{
			if (chdir("..") == -1)
			{
				ft_putstr_fd("cd: ..: not a directory\n", 2);
				free(pwd);
				return (1);
			}
		}
		else if (cmd->argv[1] && ft_strcmp(cmd->argv[1], "-") == 0)
		{
			t_envp *old = search_var(pdata->gdata->envp, "OLDPWD");
			if (!old || !old->value || chdir(old->value) == -1)
			{
				ft_putstr_fd("cd: OLDPWD not set\n", 2);
				free(pwd);
				return (1);
			}
		}
		else if (cmd->argv[1])
		{
			res = print_error(cmd->argv[1]);
			if (res == 1)
			{
				free(pwd);
				return (1);
			}
		}

		char *new_pwd = getcwd(NULL, 0);
		if (new_pwd)
		{
			update_envp(sdata->envp, "PWD", new_pwd);
			free(new_pwd);
		}
	}
	free(pwd);
	return (0);
}


