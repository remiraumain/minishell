/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:05:31 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/15 11:38:53 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_home(t_global_data *sdata, char *pwd)
{
	char	*home;
	char	*current_pwd;

	home = get_var_home(sdata->envp);
	if (!home || chdir(home) == -1)
	{
		free(pwd);
		sdata->status = 1;
		return (sdata->status);
	}
	current_pwd = getcwd(NULL, 0);
	if (current_pwd == NULL)
	{
		free(pwd);
		return (1);
	}
	update_old_pwd(sdata->envp, pwd);
	update_pwd(sdata->envp, current_pwd);
	free(pwd);
	free(current_pwd);
	sdata->status = 0;
	return (sdata->status);
}

static int	cd_dot(t_cmd *cmd, t_global_data *sdata, char *pwd)
{
	char	*current_pwd;

	if (chdir("..") == -1)
	{
		ft_putstr_fd("cd ", 2);
		print_message(cmd, ": not a directory\n");
		free(pwd);
		return (1);
	}
	current_pwd = getcwd(NULL, 0);
	if (current_pwd == NULL)
	{
		free(pwd);
		return (1);
	}
	update_old_pwd(sdata->envp, pwd);
	update_pwd(sdata->envp, current_pwd);
	free(pwd);
	free(current_pwd);
	return (0);
}

static int	process_cd(char *path, char *pwd, t_cmd *cmd, t_global_data *sdata)
{
	int		res;
	char	*current_pwd;

	res = print_error(cmd->argv[1]);
	if (res == 1)
	{
		free_path_pwd(path, pwd);
		return (1);
	}
	if (chdir(path) == -1)
	{
		free_path_pwd(path, pwd);
		return (1);
	}
	current_pwd = getcwd(NULL, 0);
	if (current_pwd == NULL)
	{
		free(pwd);
		return (1);
	}
	update_old_pwd(sdata->envp, pwd);
	update_pwd(sdata->envp, current_pwd);
	free_path_pwd(path, pwd);
	free(current_pwd);
	return (0);
}

static int	cd_relative(t_cmd *cmd, t_global_data *sdata, char *pwd)
{
	char	*path;
	int		result;
	char	*tmp;

	tmp = ft_strjoin(pwd, "/");
	if (!pwd)
		return (1);
	path = ft_strjoin(tmp, cmd->argv[1]);
	free(tmp);
	if (!path)
	{
		free(pwd);
		return (1);
	}
	result = process_cd(path, pwd, cmd, sdata);
	return (result);
}

int	exec_cd(t_cmd *cmd, t_pid_data *pdata, t_global_data *sdata)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pdata->nb_cmd == 1)
	{
		if (cmd->argv[1] && cmd->argv[2])
		{
			ft_putstr_fd("cd: too many arguments\n", 2);
			free(pwd);
			return (1);
		}
		if (!cmd->argv[1] || ft_strcmp(cmd->argv[1], "~") == 0)
			return (cd_home(sdata, pwd));
		if (ft_strcmp(cmd->argv[1], "..") == 0)
			return (cd_dot(cmd, sdata, pwd));
		if (cmd->argv[1][0] == '/')
			return (cd_slash(cmd, pwd));
		return (cd_relative(cmd, sdata, pwd));
	}
	free(pwd);
	return (0);
}
